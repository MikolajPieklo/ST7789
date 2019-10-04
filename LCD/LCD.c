/*
 * LCD.c
 *
 *  Created on: 4 Oct 2019
 *      Author: mkpk
 */

#include "LCD.h"
#include "../ST7789/ST7789.h"



void LCD_Draw_Rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color, int16_t thickness)
{
	if(x0 < x1 && y0 < y1)
	{
		ST7789_SetWindow(x0, y0, x1, y1);

		for(uint16_t x=x0;x<=x1;x++)
		{
			for(uint16_t y=y0;y<=y1;y++)
			{
				if(thickness > 0)
				{
					if(x0 + thickness > x || x1 - thickness < x || y0 + thickness > y || y1 - thickness < y)
					{
						ST7789_SetPixel(color);
					}
					else
					{
						ST7789_SetPixel(sLCD.Background_color);
					}
				}
				else
					ST7789_SetPixel(color);
			}
		}
	}
	if(x0 == 0 && x1 == 240 && y0 == 0 && y1 == 240)
	{
		sLCD.Background_color = color;
	}
}

void LCD_Draw_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color, int16_t thickness)
{
	int16_t dx, dy =0;
	int8_t stepx, stepy =0;

	if(thickness %2 != 0) thickness =+ 1;

	if(y1>y0) { dy = y1-y0; stepy = 1;} else { dy = y0-y1; stepy = -1;}
	if(x1>x0) { dx = x1-x0; stepx = 1;} else { dx = x0-x1; stepx = -1;}

	dy <<= 1;
	dx <<= 1;

	ST7789_SetWindow(x0,y0,x0,y0);
	ST7789_SetPixel(color);

	if (dx > dy)
	{
		int fraction = dy - (dx >> 1);

		while (x0 != x1)
		{
			if (fraction >= 0)
			{
				y0 += stepy;
				fraction -= dx;
			}
			x0 += stepx;
			fraction += dy;
			ST7789_SetWindow(x0,y0,x0,y0);
			ST7789_SetPixel(color);
		}
	}
	else
	{
		int fraction = dx - (dy >> 1);
		while (y0 != y1)
		{
			if (fraction >= 0)
			{
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			ST7789_SetWindow(x0,x0,y0,y0);
			ST7789_SetPixel(color);
		}
	}
}

void LCD_Draw_Circle(uint16_t x0, uint16_t y0 , uint16_t radius, uint16_t color, int16_t thickness)
{
	int16_t x, y, xchange, ychange, radiusError;
	x=radius;
	y=0;
	xchange=1-2*radius;
	ychange=1;
	radiusError=0;
	while(x>=y)
	{
		if(thickness > 0)
		{
			ST7789_SetWindow(x0+x, y0+y, x0+x, y0+y);
			ST7789_SetPixel(color);
			ST7789_SetWindow(x0-x, y0+y, x0-x, y0+y);
			ST7789_SetPixel(color);
			ST7789_SetWindow(x0-x, y0-y, x0-x, y0-y);
			ST7789_SetPixel(color);
			ST7789_SetWindow(x0+x, y0-y, x0+x, y0-y);
			ST7789_SetPixel(color);
			ST7789_SetWindow(x0+y, y0+x, x0+y, y0+x);
			ST7789_SetPixel(color);
			ST7789_SetWindow(x0-y, y0+x, x0-y, y0+x);
			ST7789_SetPixel(color);
			ST7789_SetWindow(x0-y, y0-x, x0-y, y0-x);
			ST7789_SetPixel(color);
			ST7789_SetWindow(x0+y, y0-x, x0+y, y0-x);
			ST7789_SetPixel(color);
		}
		else
		{
			LCD_Draw_Rectangle(x0-x, x0+x, y0+y, y0+y, color, -1);
			LCD_Draw_Rectangle(x0-x, x0+x, y0-y, y0-y, color, -1);
			LCD_Draw_Rectangle(x0-y, x0+y, y0+x, y0+x, color, -1);
			LCD_Draw_Rectangle(x0-y, x0+y, y0-x, y0-x, color, -1);
		}

		y++;
		radiusError+=ychange;
		ychange+=2;
		if(2*radiusError+xchange>0)
		{
			x--;
			radiusError+=xchange;
			xchange+=2;
		}
	}
	if(thickness > 1)
		LCD_Draw_Circle(x0,y0,radius-1,color,thickness-1);
}

void LCD_Draw_Bitmap_565(tImage Bitmap)
{
	uint16_t i =0;
    ST7789_SetWindow(0,0,DisplayWidth - 1, DisplayHeight - 1);
	if(Bitmap.height == DisplayHeight && Bitmap.width == DisplayWidth)
	{
	    for(i=0; i<57600; i++)
	    {
	    	ST7789_SetPixel(Bitmap.data[i]);
	    }
	}

}
