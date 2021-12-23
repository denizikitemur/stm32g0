#ifndef BSP_H_
#define BSP_H_

#include "stm32g0xx.h"
#include <stdlib.h>

/* ONBOARD LED  PC6
 * BUTTON  PA5
 * LED PB5
 *
 * SSD => A= PA1 B= PA4 C= PA5 D= PA12 E= PA11 F= PA6 G= PA7	D1 = PB4 D2= PB5 D3= PB3 D4= PA15
 * KEYPAD => R1= PB9 R2= PA8 R3= PB8 R4= PB2 C1= PB0 C2= PA9 C3= PA10 C4= PB1
 */


void system_init();


void onboardLed_Set();
void onboardLed_TurnOn();
void onboardLed_TurnOff();
void onboardLed_Toggle();

void button_set();
int button_read();
void button_interrupt();

void USART2_IRQHandler(void);
void UART_init(uint32_t);
void uart_tx(uint8_t);
uint8_t uart_rx(void);



#endif
