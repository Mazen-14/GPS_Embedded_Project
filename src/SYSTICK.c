#include "defines.h"

//Initialize the SysTick timer

void SystickInit(void) {
    NVIC_ST_CTRL_R = 0;               // Disable SysTick during setup
    NVIC_ST_RELOAD_R = 0xFFFFFF;      // Maximum reload value
    NVIC_ST_CURRENT_R = 0;            // Clear current value
    NVIC_ST_CTRL_R = 0x05;            // Enable SysTick with system clock
}

// Create a delay using SysTick timer

void Systick(uint32_t cycles) {
    NVIC_ST_CTRL_R = 0;               // Disable SysTick during setup
    NVIC_ST_CURRENT_R = 0;            // Clear current value
    NVIC_ST_RELOAD_R = cycles - 1;    // Set reload value
    NVIC_ST_CTRL_R = 0x05;            // Enable SysTick with system clock
    
    // Wait until count flag is set
    while ((NVIC_ST_CTRL_R & 0x00010000) == 0);
}

//Create a delay in seconds

void Sys_Tick(uint32_t seconds) {
    uint32_t i;
    for (i = 0; i < seconds; i++) {
        // Each second requires SYSTEM_CLOCK_HZ cycles
        Systick(16000000);  // Assuming 16MHz system clock
    }
}

//Create a delay in milliseconds

void Sys_Tick_MS(uint32_t ms) {
    uint32_t i;
    for (i = 0; i < ms; i++) {
        // Each millisecond requires SYSTEM_CLOCK_HZ/1000 cycles
        Systick(16000);  // Assuming 16MHz system clock
    }
}
