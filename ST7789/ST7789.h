#ifndef ST7789_H
#define ST7789_H

#ifndef CONFIG_PLATFORM_H
#include "../Config/config_platform.h"
#endif

#include <pigpio.h>

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define ST7789_CASET 0x2A
#define ST7789_RASET 0x2B
#define ST7789_RAMWR 0x2C


#define ST7789_BLACK    0x0000
#define ST7789_BLUE     0x001F
#define ST7789_GREEN    0x07E0
#define ST7789_RED      0xF800
#define ST7789_CYAN     0x07FF
#define ST7789_MAGENTA  0xF81F
#define ST7789_YELLOW   0xFFE0
#define ST7789_WHITE    0xFFFF


void ST7789_Init(void);
void ST7789_Reset(void);

void ST7789_SendCommand(uint8_t data);
void ST7789_SendData(uint8_t data);
void ST7789_SetWindow(uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end);

void ST7789_SendText(const uint8_t* text, uint16_t h);
void ST7789_SetPixel(uint16_t color);
void ST7789_SendChar(const uint8_t c);

#endif /* !ST7789_H */
