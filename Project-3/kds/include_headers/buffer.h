/*
 * buffer.h
 *
 *  Created on: Dec 3, 2018
 *      Author: yashm
 */

#include <stdint.h>
#include <stdio.h>
#include "dma.h"
#ifndef INCLUDE_HEADERS_BUFFER_H_
#define INCLUDE_HEADERS_BUFFER_H_
#define	coeff	2
#define GPIO_PIN(x) ((1) << (x))
uint16_t buffer[64]={1};
uint16_t* start = (uint32_t)&buffer[0];
uint16_t* mid = (uint32_t)&buffer[32];
uint32_t count=0, midcount=32;
uint16_t peak=0,old_peak_dec=0,old_peak=0;
float newAvg=0.0,lastAvg=0.0;
uint16_t receivedByte=0;
int16_t lookUpTable[164]={-221, -101, -88, -79, -74, -69, -66, -63, -60, -58, -55, -54, -52, -50, -49, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36, -36, -35, -34, -33, -33, -32, -32, -31, -30, -30, -29, -29, -28, -28, -27, -27, -26, -26, -25, -25, -24, -24, -24, -23, -23, -22, -22, -22, -21, -21, -21, -20, -20, -20, -19, -19, -19, -18, -18, -18, -17, -17, -17, -17, -16, -16, -16, -15, -15, -15, -15, -14, -14, -14, -14, -13, -13, -13, -13, -12, -12, -12, -12, -11, -11, -11, -11, -11, -10, -10, -10, -10, -10, -9, -9, -9, -9, -9, -8, -8, -8, -8, -8, -7, -7, -7, -7, -7, -7, -6, -6, -6, -6, -6, -6, -5, -5, -5, -5, -5, -5, -4, -4, -4, -4, -4, -4, -4, -3, -3, -3, -3, -3, -3, -3, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0};
char ch=0;
#endif /* INCLUDE_HEADERS_BUFFER_H_ */
