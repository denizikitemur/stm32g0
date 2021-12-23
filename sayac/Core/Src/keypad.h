/*
 * keypad.h
 *
 *  Created on: Nov 29, 2021
 *      Author: DENİZ
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32g0xx.h"

#define R1_p			(GPIOB)
#define R1_ODR			((uint16_t) (0x10))

#define R2_p			(GPIOB)
#define R2_ODR			((uint16_t) (0x20))

#define R3_p			(GPIOB)
#define R3_ODR			((uint16_t) (0x200))

#define R4_p			(GPIOA)
#define R4_ODR			((uint16_t) (0x100))

#define C1_p			(GPIOB) //PB8
#define C1_IDR			((uint16_t) (0x100))

#define C2_p			(GPIOB) //PB2
#define C2_IDR			((uint16_t) (0x4))

#define C3_p			(GPIOB) //PB0
#define C3_IDR			((uint16_t) (0x1))

#define C4_p			(GPIOA) //PA9
#define C4_IDR			((uint16_t) (0x200))

typedef enum keypadButton{keypadBut0 = 0, keypadBut1, keypadBut2, keypadBut3, keypadBut4,
	keypadBut5, keypadBut6, keypadBut7, keypadBut8, keypadBut9, keypadButA,
	keypadButB, keypadButC, keypadButD, keypadButHash, keypadButAst, none} keypadBut_t;

void setRCCForKeypad();
void setMODERForKeypad();
void setInterruptForKeypad();
void clearAllKeypadRows();
void setAllKeypadRows();
void setKeypadRow(uint8_t key);


#endif /* KEYPAD_H_ */
