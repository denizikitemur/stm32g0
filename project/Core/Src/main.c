/*
 * 	main.c
 *
 * 	Author: Hüseyin Aşcı
 * 	Description: blinky external PA4 led interval 1 sec.
 *
 */

#include "stm32g0xx.h"
#include "BSP.h"
#include "keypad.h"
#include "sevensegment.h"

enum {sine = 0, square, triangular, sawtooth, whiteNoise, randomDig} signal;
enum {dispMode = 0, dispAmp, dispFreq, input} displayMode;

keypadBut_t currentButton = none;
keypadBut_t prevButton = none;

uint8_t isInputAmp = 0;
uint8_t isInputFreq = 0;

int32_t var = 0;

int32_t amp		= 5;
int32_t freq	= 10;

void doWorkForButtons();
void sysSet();
void setSignalDisp();
void setVar();

void EXTI0_1_IRQHandler() {
	currentButton = KEY_detectButton();
	doWorkForButtons();
	EXTI -> RPR1 |= (1 << 0);
}

void EXTI2_3_IRQHandler() {
	currentButton = KEY_detectButton();
	doWorkForButtons();
	EXTI -> RPR1 |= (1 << 2);
}

void EXTI4_15_IRQHandler() {
	currentButton = KEY_detectButton();
	doWorkForButtons();
	EXTI -> RPR1 |= (1 << 8);
	EXTI -> RPR1 |= (1 << 9);
}

// bunun göz fpsine ayarlanması lazım.
// galiba 5 ms
void SysTick_Handler(){
	static volatile int8_t ct = -1;

	ct++;
	if(ct == 5) {
		SSD_disp();
		ct = 0;
	}
}

int main(void) {
	BSP_systemInit();

    return 0;
}


void doWorkForButtons() {
	switch(currentButton) {
	case keypadButC:
		signal++;
		if(signal == 6)
			signal = 0;
		break;
	case keypadButD:
		displayMode++;
		if(displayMode >= 3)
			displayMode = 0;
		break;
	case keypadButA:
		displayMode = input;
		isInputAmp = 1;
		break;
	case keypadButB:
		displayMode = input;
		isInputFreq = 1;
		break;
	case keypadButHash:
		amp = isInputAmp ? var : amp;
		freq = isInputFreq ? var : freq;
		isInputAmp = 0;
		isInputFreq = 0;
		var = 0;
		displayMode = dispMode;
		break;
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		setVar();
		break;
	default:
		//..
		break;
	}


	sysSet();
}

void sysSet() {
	switch(displayMode) {
	case dispAmp:
		SSD_getDigits(amp);
		break;
	case dispFreq:
		SSD_getDigits(freq);
		break;
	case dispMode:
		setSignalDisp();
		break;
	case input:
		SSD_getDigits(var);
		break;

	}
}

void setSignalDisp(){
	switch(signal) {
	case sine:
		SSD_setSine();
		break;
	case square:
		SSD_setSquare();
		break;
	case triangular:
		SSD_setTri();
		break;
	case sawtooth:
		SSD_setRamp();
		break;
	case whiteNoise:
		SSD_setWhiteNoise();
		break;
	case randomDig:
		SSD_setRandDigital();
		break;
	}
}

void setVar() {
	var *= 10;
	var += currentButton;
	SSD_getDigits(var);
}
