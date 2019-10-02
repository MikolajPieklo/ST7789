#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "ST7789/ST7789.h"

#include <pigpio.h>

int main (void)
{
    gpioInitialise();
    spiOpen(0,20000000,3);
    	
    gpioSetMode(PIN_RST, PI_OUTPUT);
    gpioSetMode(PIN_DC, PI_OUTPUT);
    gpioSetMode(PIN_LED, PI_OUTPUT);
    
    ST7789_Reset();
    ST7789_Init();

    LCD_Draw_Rectangle(0,240,0,240, ST7789_RED, -1);
    LCD_Draw_Rectangle(50,200,50,200, ST7789_BLACK, 2);
    LCD_Draw_Line(60,160,80,190,ST7789_BLACK,10);
    /*ST7789_SendText("Hey\0", 50);
    ST7789_SendText("5:1\0", 100);
    ST7789_SendText("Chiny", 150);
    ST7789_SetWindow(0,239,0,239);*/


    /*while(1)
    {
       ST7789_SetPixel(ST7789_GREEN);
       gpioSleep(0,2,0);
       ST7789_SetPixel(ST7789_BLUE);
       gpioSleep(0,2,0);
       ST7789_SetPixel(ST7789_RED);
       gpioSleep(0,2,0);
       ST7789_SetPixel(ST7789_YELLOW);
       gpioSleep(0,2,0);
       ST7789_SetPixel(ST7789_MAGENTA);
       gpioSleep(0,2,0);
    }*/
    
  	return 0 ;
}
