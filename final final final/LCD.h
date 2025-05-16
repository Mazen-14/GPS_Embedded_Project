#ifndef LCD_H
#define LCD_H


void LCD_Init(void);
void LCD_Clear(void);
void LCD_Cmd(unsigned char command);
void LCD_Char(unsigned char data);
void LCD_String(char *str);
void delayMs(int n);
void LCD_GotoLine(uint8_t line) ;

#endif
