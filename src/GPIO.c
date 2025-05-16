#include "defines.h"
#define BUZZER_PORT GPIO_PORTD_DATA_R
#define BUZZER_PIN  0x01  

//Initialize Port F for LEDs and buttons

void PortF_Init(void) {

    SYSCTL_RCGCGPIO_R |= 0x20;              
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);   

    GPIO_PORTF_LOCK_R = 0x4C4F434B;        
    GPIO_PORTF_CR_R |= 0x1F;                 
    
    GPIO_PORTF_DIR_R = (GPIO_PORTF_DIR_R & ~0x11) | 0x0E;  
    
    GPIO_PORTF_PUR_R |= 0x11;              
    
    GPIO_PORTF_AFSEL_R &= ~0x1F;            
    
    GPIO_PORTF_DEN_R |= 0x1F;                
    

    GPIO_PORTF_AMSEL_R &= ~0x1F;           
    

    GPIO_PORTF_DATA_R &= ~0x0E; 
    
    GPIO_PORTF_IS_R &= ~0x1;  
    GPIO_PORTF_IBE_R &= ~0x1;  // Not both edges
    GPIO_PORTF_IEV_R &= ~0x1;  // Falling edge trigger
    GPIO_PORTF_IM_R |= 0x1;    // Unmask interrupt
    
    // Enable Port F interrupts in NVIC
    NVIC_EN0_R |= (1 << 30); 
    
    // Enable processor interrupts
    __asm("CPSIE I");
    
    // Set interrupt priority
    NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | 0x00200000;             
}

/**
 * @brief System initialization - Configure system clock
 */
void SystemInit(void) {
    // System clock config for 80 MHz
    SYSCTL_RCC2_R |= 0x80000000;       // USERCC2
    SYSCTL_RCC2_R |= 0x00000800;       // BYPASS2
    SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x000007C0) + 0x00000540;
    SYSCTL_RCC2_R &= ~0x00000070;
    SYSCTL_RCC2_R &= ~0x00002000;      // Activate PLL
    SYSCTL_RCC2_R |= 0x40000000;       // Use 400 MHz PLL
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) + (4 << 22); // Divide by 5 = 80 MHz
    while ((SYSCTL_RIS_R & 0x00000040) == 0);
    SYSCTL_RCC2_R &= ~0x00000800;
}

//Initialize Port D for buzzer control

void PortD_Buzzer_Init(void) {

    SYSCTL_RCGCGPIO_R |= 0x08;         
    while ((SYSCTL_PRGPIO_R & 0x08) == 0); 

    GPIO_PORTD_LOCK_R = 0x4C4F434B;    
    GPIO_PORTD_CR_R |= 0x01;           
    
    GPIO_PORTD_DIR_R |= 0x01;          
    
    GPIO_PORTD_DEN_R |= 0x01;          
}

//Sound the buzzer briefly
 
void Buzzer_Ring(void) {
    // Turn buzzer ON
    GPIO_PORTD_DATA_R |= 0x01;
    
    // Wait for a short duration
    Sys_Tick(3);
    
    // Turn buzzer OFF
    GPIO_PORTD_DATA_R &= ~0x01;
}

//Port F interrupt handler
  
void GPIOF_Handler(void) {
    // Display interrupt notification on LCD
    LCD_Clear();
    LCD_GotoLine(0);
    LCD_String("This is");
    LCD_GotoLine(1);
    LCD_String("Interrupt!!!");
    
    // Clear the interrupt flag
    GPIO_PORTF_ICR_R |= 0x1;
}
