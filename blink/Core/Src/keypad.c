/*
 * keypad.c
 *
 *  Created on: Nov 15, 2021
 *      Author: huseyinasci
 */

#include "keypad.h"

void setRCCForKeypad() {
	// A ve B pinlerini aç
	RCC -> IOPENR |= (3U);
}

void setMODERForKeypad() {
	// ROW AYARLARI
	R1_p -> MODER &= ~(3U << 4*2);
	R1_p -> MODER |= (1U << 4*2);

	R2_p -> MODER &= ~(3U << 5*2);
	R2_p -> MODER |= (1U << 5*2);

	R3_p -> MODER &= ~(3U << 9*2);
	R3_p -> MODER |= (1U << 9*2);

	R4_p -> MODER &= ~(3U << 8*2);
	R4_p -> MODER |= (1U << 8*2);

	//COLUMN (INPUT) AYARLARI
	C1_p -> MODER &= ~(3U << 8*2);
	C2_p -> MODER &= ~(3U << 2*2);
	C3_p -> MODER &= ~(3U << 0*2);
	C4_p -> MODER &= ~(3U << 9*2);

	//COLUMN PUPDR AYARLARI
	C1_p -> PUPDR |= (2U << 8*2);
	C2_p -> PUPDR |= (2U << 2*2);
	C3_p -> PUPDR |= (2U << 0*2);
	C4_p -> PUPDR |= (2U << 9*2);
}

void setInterruptForKeypad(){
	// C1 -> PB8
	EXTI -> EXTICR[2] |= (1U << 0*8);

	// C2 -> PB2
	EXTI -> EXTICR[0] |= (1U << 2*8);

	// C3 -> PB0
	EXTI -> EXTICR[0] |= (1U << 0*8);

	// C4 -> PA9
	EXTI -> EXTICR[2] |= (0U << 1*8);

	EXTI -> RTSR1 |= (1U << 9);
	EXTI -> RTSR1 |= (1U << 0);
	EXTI -> RTSR1 |= (1U << 2);
	EXTI -> RTSR1 |= (1U << 8);

	EXTI -> IMR1 |= (1U << 9);
	EXTI -> IMR1 |= (1U << 0);
	EXTI -> IMR1 |= (1U << 2);
	EXTI -> IMR1 |= (1U << 8);

	NVIC_SetPriority(EXTI0_1_IRQn, 0);
	NVIC_EnableIRQ(EXTI0_1_IRQn);

	NVIC_SetPriority(EXTI2_3_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);

	NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void clearAllKeypadRows() {
	R1_p -> ODR &= (~R1_ODR);
	R2_p -> ODR &= (~R2_ODR);
	R3_p -> ODR &= (~R3_ODR);
	R4_p -> ODR &= (~R4_ODR);
}

void setAllKeypadRows() {
	R1_p -> ODR |= (R1_ODR);
	R2_p -> ODR |= (R2_ODR);
	R3_p -> ODR |= (R3_ODR);
	R4_p -> ODR |= (R4_ODR);
}

keypadBut_t detectButton() {
	clearAllKeypadRows();
	keypadBut_t button = none;

	// sadece R1 açık
	setKeypadRow(1);
	if(C1_p -> IDR & C1_IDR) {
		//1
		button = keypadBut1;
	} else if(C2_p -> IDR & C2_IDR) {
		//2
		button = keypadBut2;
	} else if(C3_p -> IDR & C3_IDR) {
		//3
		button = keypadBut3;
	} else if(C4_p -> IDR & C4_IDR) {
		//A
		button = keypadButA;
	}

	// sadece R2 açık
	setKeypadRow(2);
	if(C1_p -> IDR & C1_IDR) {
		//4
		button = keypadBut4;
	} else if(C2_p -> IDR & C2_IDR) {
		//5
		button = keypadBut5;
	} else if(C3_p -> IDR & C3_IDR) {
		//6
		button = keypadBut6;
	} else if(C4_p -> IDR & C4_IDR) {
		//B
		button = keypadButB;
	}

	// sadece R3 açık
	setKeypadRow(3);
	if(C1_p -> IDR & C1_IDR) {
		//7
		button = keypadBut7;
	} else if(C2_p -> IDR & C2_IDR) {
		//8
		button = keypadBut8;
	} else if(C3_p -> IDR & C3_IDR) {
		//9
		button = keypadBut9;
	} else if(C4_p -> IDR & C4_IDR) {
		//C
		button = keypadButC;
	}

	// sadece R4 açık
	setKeypadRow(4);
	if(C1_p -> IDR & C1_IDR) {
		//*
		button = keypadButAst;
	} else if(C2_p -> IDR & C2_IDR) {
		//0
		button = keypadBut0;
	} else if(C3_p -> IDR & C3_IDR) {
		//#
		button = keypadButHash;
	} else if(C4_p -> IDR & C4_IDR) {
		//D
		button = keypadButD;
	}

	setAllKeypadRows();

	return button;
}

void setKeypadRow(uint8_t key) {
	clearAllKeypadRows();

	switch(key){
	case 1:
		R1_p -> ODR |= (R1_ODR);
		break;
	case 2:
		R2_p -> ODR |= (R2_ODR);
		break;
	case 3:
		R3_p -> ODR |= (R3_ODR);
		break;
	case 4:
		R4_p -> ODR |= (R4_ODR);
		break;
	default:
		// allah kurtarsın
		break;
	}
}
