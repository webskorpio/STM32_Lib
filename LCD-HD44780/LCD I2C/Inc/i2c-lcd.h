#include "stm32f1xx_hal.h"


void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_gotoxy(uint8_t x, uint8_t y);


/** Display size ------------------------------------------------------------ */
// Number of visible lines of the display (1 or 2/4)
#define LCD16X2_LINES					4
// Visible characters per line of the display
#define LCD16X2_DISP_LENGTH		20
// DDRAM address of first char of line 1
#define LCD16X2_START_LINE_1	0x00
// DDRAM address of first char of line 2
#define LCD16X2_START_LINE_2	0x40
// DDRAM address of first char of line 3
#define LCD16X2_START_LINE_3	0x14
// DDRAM address of first char of line 4
#define LCD16X2_START_LINE_4	0x54

#define CLEARROW 0x01

#define LCD16X2_SET_DDRAM_ADDRESS 0x80

