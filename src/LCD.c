#include "defines.h"

//LCD control pin definitions

#define RS 0x10  // PB4 - Register Select
#define EN 0x20  // PB5 - Enable

//Generate an enable pulse to latch data into LCD

void LCD_EnablePulse(void) {
    GPIO_PORTB_DATA_R |= EN;    // Set enable high
    Sys_Tick_MS(1);             // Wait 1ms
    GPIO_PORTB_DATA_R &= ~EN;   // Set enable low
    Sys_Tick_MS(1);             // Wait 1ms
}

//Send 4 bits of data to the LCD

void LCD_Send4Bits(uint8_t data) {
    // Update data pins (PB0-PB3) while preserving other pins
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & ~0x0F) | (data & 0x0F);
    LCD_EnablePulse();
}

/**
 * @brief Send a command to the LCD
 * 
 * @param command The command byte to send
 */
void LCD_Cmd(unsigned char command) {
    GPIO_PORTB_DATA_R &= ~RS;          // RS=0 for command mode
    LCD_Send4Bits(command >> 4);       // Send high nibble
    LCD_Send4Bits(command);            // Send low nibble
    Sys_Tick_MS(2);                    // Wait for command to complete
}

//Clear the LCD display
 
void LCD_Clear(void) {
    GPIO_PORTB_DATA_R &= ~RS;          // RS=0 for command mode
    LCD_Send4Bits(0x00);               // High nibble of clear command (0x01)
    LCD_Send4Bits(0x01);               // Low nibble of clear command (0x01)
    Sys_Tick_MS(2);                    // Wait for clear to complete (needs ~1.52ms)
}

//Position the cursor at the beginning of specified line
 
void LCD_GotoLine(uint8_t line) {
    if (line == 0) {
        LCD_Cmd(0x80);                 // Move to first line (address 0x00)
    } else {
        LCD_Cmd(0xC0);                 // Move to second line (address 0x40)
    }
}

//Display a character on the LCD

void LCD_Char(unsigned char data) {
    GPIO_PORTB_DATA_R |= RS;           // RS=1 for data mode
    LCD_Send4Bits(data >> 4);          // Send high nibble
    LCD_Send4Bits(data);               // Send low nibble
    Sys_Tick_MS(2);                    // Wait for character to be displayed
}

//Display a string on the LCD

void LCD_String(char *str) {
    while (*str) {
        LCD_Char(*str++);
    }
}

//Initialize the LCD

void LCD_Init(void) {

    SYSCTL_RCGCGPIO_R |= 0x02;
    while ((SYSCTL_PRGPIO_R & 0x02) == 0);

    GPIO_PORTB_DIR_R |= 0x3F;  
    GPIO_PORTB_DEN_R |= 0x3F;   
    
    // Wait for LCD to power up
    Sys_Tick_MS(20);
    
    // Initialize LCD to 4-bit mode
    LCD_Send4Bits(0x03);        // Function set (first time)
    Sys_Tick_MS(5);
    LCD_Send4Bits(0x03);        // Function set (second time)
    Sys_Tick_MS(1);
    LCD_Send4Bits(0x03);        // Function set (third time)
    Sys_Tick_MS(1);
    LCD_Send4Bits(0x02);        // Set to 4-bit mode
    
    LCD_Cmd(0x28);              // 4-bit, 2 line, 5x8 font
    LCD_Cmd(0x06);              // Entry mode: cursor moves right
    LCD_Cmd(0x01);              // Clear display
    LCD_Cmd(0x0F);              // Display ON, cursor ON, blink ON
}
