#include "defines.h"

//Read a character from UART5

char UART5_Read(void) {
    // Wait until receive FIFO is not empty (RXFE = 0)
    while (UART5_FR_R & 0x10);
    
    // Return the received character
    return (char)(UART5_DR_R & 0xFF);
}

//Write a character to UART5

void UART5_Write(char data) {
    // Wait until transmit FIFO is not full (TXFF = 0)
    while (UART5_FR_R & 0x20);
    
    // Write the character to the data register
    UART5_DR_R = data;
}

//Initialize UART5 for communication with GPS module

void UART5_Init(void) {
    // Enable clock to UART5 and GPIO Port E
    SYSCTL_RCGCUART_R |= 0x20;        // Enable UART5 clock (bit 5)
    SYSCTL_RCGCGPIO_R |= 0x10;        // Enable GPIO Port E clock (bit 4)
    while ((SYSCTL_PRGPIO_R & 0x10) == 0); // Wait for Port E to be ready
    UART5_CTL_R &= ~0x01;

    UART5_IBRD_R = 104;
    UART5_FBRD_R = 11;
    
    UART5_LCRH_R = 0x70;
    
    GPIO_PORTE_AFSEL_R |= 0x30;        // Enable alternate function on PE4, PE5
    
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & ~0x00FF0000) | 0x00110000;

    GPIO_PORTE_DEN_R |= 0x30;
    
    GPIO_PORTE_DIR_R |= 0x20;          // PE5 (TX) as output
    GPIO_PORTE_DIR_R &= ~0x10;         // PE4 (RX) as input
    
    UART5_CTL_R |= 0x301;              // Enable UART5, TXE, RXE
}
