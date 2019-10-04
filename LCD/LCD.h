/*
 * LCD.h
 *
 *  Created on: 4 Oct 2019
 *      Author: mkpk
 */

#ifndef ST7789_LCD_LCD_H_
#define ST7789_LCD_LCD_H_

#include "stdint.h"
#include "../Images/Images.h"
#include "../Config/config_platform.h"

void LCD_Draw_Rectangle	(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint16_t color, int16_t thickness);
void LCD_Draw_Line		(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint16_t color, int16_t thickness);
void LCD_Draw_Circle	(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color, int16_t Fill);

void LCD_Draw_Bitmap_565(tImage Bitmap);

#endif /* ST7789_LCD_LCD_H_ */
