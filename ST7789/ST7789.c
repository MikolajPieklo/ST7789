#include "ST7789.h"
#include "../Fonts/Font_36.h"

void ST7789_Reset(){
    gpioWrite(PIN_RST, PI_HIGH);
    gpioDelay(100);
    gpioWrite(PIN_RST, PI_LOW);
    gpioDelay(100);
    gpioWrite(PIN_RST, PI_HIGH);
    gpioDelay(100);
}

void ST7789_Init(){

	sLCD.Background_color = ST7789_WHITE;
    gpioDelay(10);

    ST7789_SendCommand(0x11); //Sleep Out
    gpioDelay(150);

    ST7789_SendCommand(0x36); //MADCTL: Memory Data Access Control
    ST7789_SendData(0x00);

    ST7789_SendCommand(0x3A); //COLMOD: Interface Pixel Format 16bit/pixel
    ST7789_SendData(0x05);

    ST7789_SendCommand(0xB2); //PORCTRL: Porch Setting
    ST7789_SendData(0x0C);
    ST7789_SendData(0x0C);

    ST7789_SendCommand(0xB7); //GCTRL: Gate Control
    ST7789_SendData(0x35);

    ST7789_SendCommand(0xBB); //VCOMS: VCOM Setting
    ST7789_SendData(0x1A);

    ST7789_SendCommand(0xC0); //LCMCTRL: LCM Control
    ST7789_SendData(0x2C);

    ST7789_SendCommand(0xC2); //VDVVRHEN: VDV and VRH Command Enable
    ST7789_SendData(0x01);

    ST7789_SendCommand(0xC3); //VRHS: VRH Set
    ST7789_SendData(0x0B);

    ST7789_SendCommand(0xC4); //VDVS (C4h): VDV Set
    ST7789_SendData(0x20);

    ST7789_SendCommand(0xC6); //FRCTRL2: Frame Rate Control in Normal Mode
    ST7789_SendData(0x0F);

    ST7789_SendCommand(0xD0); //PWCTRL1: Power Control 1
    ST7789_SendData(0xA4);
    ST7789_SendData(0xA1);

    ST7789_SendCommand(0x21); //INVON: Display Inversion On

    ST7789_SendCommand(0xE0); //PVGAMCTRL: Positive Voltage Gamma Control
    ST7789_SendData(0x00);
    ST7789_SendData(0x19);
    ST7789_SendData(0x1E);
    ST7789_SendData(0x0A);
    ST7789_SendData(0x09);
    ST7789_SendData(0x15);
    ST7789_SendData(0x3D);
    ST7789_SendData(0x44);
    ST7789_SendData(0x51);
    ST7789_SendData(0x12);
    ST7789_SendData(0x03);
    ST7789_SendData(0x00);
    ST7789_SendData(0x3F);
    ST7789_SendData(0x3F);

    ST7789_SendCommand(0xE1); //NVGAMCTRL: Negative Voltage Gamma Control
    ST7789_SendData(0x00);
    ST7789_SendData(0x18);
    ST7789_SendData(0x1E);
    ST7789_SendData(0x0A);
    ST7789_SendData(0x09);
    ST7789_SendData(0x25);
    ST7789_SendData(0x3F);
    ST7789_SendData(0x43);
    ST7789_SendData(0x52);
    ST7789_SendData(0x33);
    ST7789_SendData(0x03);
    ST7789_SendData(0x00);
    ST7789_SendData(0x3F);
    ST7789_SendData(0x3F);

    ST7789_SendCommand(0x29); //DISPON: Display On

    gpioDelay(100);
    //delay(100);
}

void ST7789_SetPixel(uint16_t color){
	ST7789_SendData((uint8_t)(color>>8));
	ST7789_SendData((uint8_t)(color&0xFF));
}

void ST7789_SendChar(const uint8_t c){
    uint16_t i = 0;
    uint16_t j = 0;
    const uint8_t* p;

    for(i =0; i < 126; i++)
    {
        p = &Font.chars[c-32].image->data[i];
        for(j = 0; j < 8; j++)
        {
			if((*p & (0x80>>j)) != 0)
            {
				ST7789_SendData(0x00);
				ST7789_SendData(0x00);
            }
            else
            {
            	ST7789_SetPixel(sLCD.Background_color);
            }
        }
    }
}

void ST7789_SendCommand(uint8_t data){
    gpioWrite(PIN_DC, PI_LOW);
    spiWrite(0,&data,1);
}

void ST7789_SendData(uint8_t data){
    gpioWrite(PIN_DC, PI_HIGH);
    spiWrite(0,&data,1);
}

void ST7789_SetWindow(uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end){

	ST7789_SendCommand(ST7789_CASET);//Column addr set
	ST7789_SendData(x_start >> 8);
	ST7789_SendData(x_start);// XSTART
	ST7789_SendData(x_end >> 8);
	ST7789_SendData(x_end);// XEND
	ST7789_SendCommand(ST7789_RASET);//Row addr set
	ST7789_SendData(y_start >> 8);
	ST7789_SendData(y_start);//YSTART
	ST7789_SendData(y_end >> 8);
	ST7789_SendData(y_end);// YEND
	ST7789_SendCommand(ST7789_RAMWR);//write to RAM
}

void ST7789_SendText(const uint8_t* text, uint16_t h){
	uint8_t i = 0;
	uint8_t len = strlen(text);

	for(i=0; i<len;i ++)
	{
		ST7789_SetWindow(50 + 23 * i, 73 + 23 * i, h, h + 41);
		ST7789_SendChar(*(text + i));
	}
}

void LCD_Draw_Rectangle(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint16_t color, int16_t thickness)
{
	if(x0 < x1 && y0 < y1)
	{
		ST7789_SetWindow(x0,x1,y0,y1);

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
						ST7789_SetPixel(sLCD.Background_color);// To do background
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

void LCD_Draw_Line(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint16_t color, uint16_t thickness)
{
	int16_t dx, dy =0;
	int8_t stepx, stepy =0;

	if(thickness %2 != 0) thickness =+ 1;

	if(x1>x0) {dx = x1 - x0; stepx =1;} else { dx = x0 - x1; stepx = -1;}
	if(y1>y0) {dy = y1 - y0; stepy =1;} else { dy = y0 - y1; stepy = -1;}

	if(dx > dy)
	{

	}
	else if(dx == dy)
	{
		for(uint16_t x = x0; x < x1; x++)
		{
			ST7789_SetWindow(x, x, x, x);
			ST7789_SetPixel(color);
		}
	}
	else if (dx < dy)
	{

	}
	else
	{

	}
}
