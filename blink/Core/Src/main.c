/*
 * main.c
 *
 * author: Saddam
 *
 * description: making a C4 BOMB
 */

#include "stm32g0xx.h"
//#include <math.h>
#include "sevensegment.h"
#include "keypad.h"

void delay(volatile uint32_t);
void test();
void doWorkForButton();

keypadBut_t button;

void EXTI0_1_IRQHandler() {
	button = detectButton();
	doWorkForButton();
	EXTI -> RPR1 |= (1 << 0);
}

void EXTI2_3_IRQHandler() {
	/*
		button = detectButton();
		doWorkForButton();
	*/
	EXTI -> RPR1 |= (1 << 2);
}

void EXTI4_15_IRQHandler() {
	button = detectButton();
	doWorkForButton();
	EXTI -> RPR1 |= (1 << 8);
	EXTI -> RPR1 |= (1 << 9);
}

int main(void) {
	setRCCForSSD();
	setMODERForSSD();

	setRCCForKeypad();
	setMODERForKeypad();
	setInterruptForKeypad();

	setAllKeypadRows();

	digitsSSD[0] = 0;
	digitsSSD[1] = 0;
	digitsSSD[2] = 0;
	digitsSSD[3] = 0;

	for(button = 1; button <=9; button++) {
		for(int i = 1000; i > 0; i--)
			dispArrayInSSD();
		doWorkForButton();
		if(button == 9) {
			button = 0;
		}
	}

	while(1){
		dispArrayInSSD();
	}

    return 0;
}

void doWorkForButton(){
	//**** doWorkForButton
	static int i = 0;
	digitsSSD[i % 4] = button;
	i++;
}

void test() {
	volatile uint8_t dig1 = 0, dig2 = 0, dig3 = 0, dig4 = 0;

	for(uint32_t i = 0; i < 999999; i++) {
		if(i % 100 == 0) {
			dig1++;
			if(dig1 == 10) {
						dig2++;
						dig1 = 0;
						if(dig2 == 10)
						{
							dig3++;
							dig2 = 0;
							if(dig3 == 10) {
								dig4++;
								dig3 = 0;
								if(dig4 == 10) {
									break;
								}
							}
						}
					}
		}

		dispNumberDigitInSSD(dig4, (uint8_t) 1);
		delay(1000);
		dispNumberDigitInSSD(dig3, (uint8_t) 2);
		delay(1000);
		dispNumberDigitInSSD(dig2, (uint8_t) 3);
		delay(1000);
		dispNumberDigitInSSD(dig1, (uint8_t) 4);
		delay(1000);
	}
}

