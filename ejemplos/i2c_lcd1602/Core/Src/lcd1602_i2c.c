/*
 * lcd1602_i2c.c
 *
 *  Created on: Mar 29, 2023
 *      Author: carlassaraf
 */

#include "lcd1602_i2c.h"

// I2C handler
I2C_HandleTypeDef *i2c1;

/* Quick helper function for single byte transfers */
void i2c_write_byte(uint8_t val) {

    HAL_I2C_Master_Transmit(i2c1, ADDR, &val, 1, 100);
}

void lcd_toggle_enable(uint8_t val) {
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work
	HAL_Delay(1);
    i2c_write_byte(val | LCD_ENABLE_BIT);
	HAL_Delay(1);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
	HAL_Delay(1);
}

// The display is sent a byte as two separate nibble transfers
void lcd_send_byte(uint8_t val, int mode) {
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear(void) {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

// go to location on LCD
void lcd_set_cursor(int line, int position) {
    int val = (line == 0) ? 0x80 + position : 0xC0 + position;
    lcd_send_byte(val, LCD_COMMAND);
}

void lcd_string(const char *s) {
    while (*s) {
        lcd_char(*s++);
    }
}

void lcd_init(I2C_HandleTypeDef *hi2c1) {
	// Guardo el I2C usado
	i2c1 = hi2c1;

    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x02, LCD_COMMAND);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    lcd_clear();
}
