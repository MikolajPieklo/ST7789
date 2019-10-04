/*
 * Images.h
 *
 *  Created on: 3 Oct 2019
 *      Author: mkpk
 */

#ifndef ST7789_IMAGES_IMAGES_H_
#define ST7789_IMAGES_IMAGES_H_

#include <stdint.h>

 typedef struct {
     const uint16_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;

extern const tImage blackbackground;
extern const tImage pluto;
extern const tImage neptun;
extern const tImage uranus;
extern const tImage saturn;
extern const tImage jupiter;
extern const tImage mars;

#endif /* ST7789_IMAGES_IMAGES_H_ */
