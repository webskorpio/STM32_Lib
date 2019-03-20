
/** Put this in the src folder **/

#include "i2c-lcd.h"

extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup


void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_init (void)
{
	lcd_send_cmd (0x02);
	lcd_send_cmd (0x28);
	lcd_send_cmd (0x0c);
	lcd_send_cmd (LCD16X2_SET_DDRAM_ADDRESS);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

/**
  ******************************************************************************
  * @brief	Set LCD cursor to specific position.
  * @param	LCD column (x)
  * @param	LCD row (y)
  * @retval	None
  ******************************************************************************
  */
void lcd_gotoxy(uint8_t x, uint8_t y)
{
	

#if LCD16X2_LINES == 1 
	lcd16X2_write_command(LCD16X2_SET_DDRAM_ADDRESS |
		(LCD16X2_START_LINE_1 + x));
#elif LCD16X2_LINES == 2
	if (y == 0)
		lcd16x2_write_command(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_1 + x));
	else
		lcd16x2_write_command(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_2 + x));
#elif LCD16X2_LINES == 4
	if (y == 0)
		lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_1 + x));
	else if (y == 1)
		lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_2 + x));
	else if (y == 2)
		lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_3 + x));
	else
		lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_4 + x));
#endif
}



