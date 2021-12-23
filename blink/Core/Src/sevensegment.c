/*
 * sevenSegment.c
 *
 *  Created on: Nov 14, 2021
 *      Author: huseyinasci
 */

#include "sevensegment.h"
#include "stm32g0xx.h"
#include <stdlib.h>
#include <math.h>

void setAllSSDDigits() {
	// ALL DIGIT ODR
	DIGIT_1_P -> ODR |= DIGIT_1;
	DIGIT_2_P -> ODR |= DIGIT_2;
	DIGIT_3_P -> ODR |= DIGIT_3;
	DIGIT_4_P -> ODR |= DIGIT_4;
}

void resetAllSSDDigits() {
	DIGIT_1_P -> ODR &= ~DIGIT_1;
	DIGIT_2_P -> ODR &= ~DIGIT_2;
	DIGIT_3_P -> ODR &= ~DIGIT_3;
	DIGIT_4_P -> ODR &= ~DIGIT_4;
}

void setSSDDigit(uint8_t digit) {
   /*
    * 		   D1	=>	PA7
	* 		   D2	=>	PB3
	* 		   D3	=>	PA10
	* 		   D4	=>	PB1
    */

	// önce hepsini kapat
	resetAllSSDDigits();
	// **** //

	switch(digit) {
	case 1:
		DIGIT_1_P -> ODR |= DIGIT_1;
		break;
	case 2:
		DIGIT_2_P -> ODR |= DIGIT_2;
		break;
	case 3:
		DIGIT_3_P -> ODR |= DIGIT_3;
		break;
	case 4:
		DIGIT_4_P -> ODR |= DIGIT_4;
		break;
	default:
		break;
	}
}

void dispNumberDigitInSSD(uint8_t zeroToTen, uint8_t SSDDigit) {
	setSSDDigit(SSDDigit);

	SEGMENT_P -> ODR |= SSD_CLEAR;

	switch(zeroToTen){
	case 0:
		SEGMENT_P -> ODR &= SSD_ZERO;
		break;
	case 1:
		SEGMENT_P -> ODR &= SSD_ONE;
		break;
	case 2:
		SEGMENT_P -> ODR &= SSD_TWO;
		break;
	case 3:
		SEGMENT_P -> ODR &= SSD_THREE;
		break;
	case 4:
		SEGMENT_P -> ODR &= SSD_FOUR;
		break;
	case 5:
		SEGMENT_P -> ODR &= SSD_FIVE;
		break;
	case 6:
		SEGMENT_P -> ODR &= SSD_SIX;
		break;
	case 7:
		SEGMENT_P -> ODR &= SSD_SEVEN;
		break;
	case 8:
		SEGMENT_P -> ODR &= SSD_EIGHT;
		break;
	case 9:
		SEGMENT_P -> ODR &= SSD_NINE;
		break;
	case 10:
		SEGMENT_P -> ODR &= SSD_M_HYPEN;
	}
}

//Loopun içinde çağırman lazım.
int dispNumberInSSD(int32_t val){
	int16_t len = countDigits(val);
	if(len > 4) {
		return -1;
	}

	getDigits(val);

	if(val < 0 && len > 3) {
		return -1;
	}

	if(val < 0) {
		digitsSSD[3] = digitsSSD[2];
		digitsSSD[2] = digitsSSD[1];
		digitsSSD[1] = digitsSSD[0];
		digitsSSD[0] = 10;
	}

	dispNumberDigitInSSD(digitsSSD[0], 1);
	delay(DELAY_FOR_SSD);
	dispNumberDigitInSSD(digitsSSD[1], 2);
	delay(DELAY_FOR_SSD);
	dispNumberDigitInSSD(digitsSSD[2], 3);
	delay(DELAY_FOR_SSD);
	dispNumberDigitInSSD(digitsSSD[3], 4);
	delay(DELAY_FOR_SSD);
	return 0;
}

//Loopun içinde çağırman lazım.
//digitsSSD ile gösterir.
void dispArrayInSSD(){
		dispNumberDigitInSSD(digitsSSD[0], 1);
		delay(DELAY_FOR_SSD);
		dispNumberDigitInSSD(digitsSSD[1], 2);
		delay(DELAY_FOR_SSD);
		dispNumberDigitInSSD(digitsSSD[2], 3);
		delay(DELAY_FOR_SSD);
		dispNumberDigitInSSD(digitsSSD[3], 4);
		delay(DELAY_FOR_SSD);
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

// PINLERE GORE AYARLAMAN LAZIM
void setRCCForSSD() {
	// A ve B pinlerini aç
	RCC -> IOPENR |= (3U);
}

// PINLERE GORE AYARLAMAN LAZIM
void setMODERForSSD() {
	// A için (SADECE SSD PINLERI)
	// 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
	// xx xx xx 01 01 01 xx xx 01 01 01 01 xx xx 01 01  lazım
	// 00 00 00	01 01 01 00 00 01 01 01 01 00 00 01 01 = 0x1505505  orlamak için
	// 11 11 11	01 01 01 11 11 01 01 01 01 11 11 01 01 = 0xFD5F55F5 andlemek için
	GPIOA -> MODER |= (uint32_t) (0x1505505);
	GPIOA -> MODER &= (uint32_t) (0xFD5F55F5);

	// B için (SADECE SSD PINLERI)
	// 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
	// xx xx xx xx xx xx xx xx xx xx xx xx 01 xx 01 xx
	// 	  								   01 00 01 00 = 0x44 orlamak için
	// 11 11 11 11 11 11 11 11 11 11 11 11 01 11 01 11 = 0xFFFFFF77 andlemek için
	GPIOB -> MODER |= (uint32_t) (0x44);
	GPIOB -> MODER &= (uint32_t) (0xFFFFFF77);
}

//**** UTIL ****//
void getDigits(int32_t val){
		int16_t len = countDigits(val);
		val = abs(val);

		for (int16_t i = (int16_t) (len - 1); i >= 0; digitsSSD[i--] = (uint8_t)(val % 10), val /= 10){}
}

int16_t countDigits(int32_t val){
	return val == 0 ? (int16_t) 1 : (int16_t) (log10(abs(val)) + 1);
}
