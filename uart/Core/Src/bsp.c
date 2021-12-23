/*
 * bsp.c
 *
 *  Created on: Dec 15, 2021
 *      Author: DENİZ
 */


/*
 * bsp.c
 *
 *  Created on: Dec 1, 2021
 *      Author: antih
 */
#include "stm32g0xx.h"
#include "bsp.h"

#define LEDDELAY    160000

static volatile uint32_t tick = 0;

void system_init(){

	__disable_irq();
	onboardLed_Set();
	button_set();
	SysTick_Config(SystemCoreClock / 1000);
	UART_init(9600);
	__enable_irq();
}


//INITILIZE ONBOARD LED CONNECTED TO PC6 PIN AND CONFIGURATION
void onboardLed_Set(){
    /* Enable GPIOC clock */
    RCC->IOPENR |= (1U << 2);
    /* Setup PC6 as output for onboard led*/
    GPIOC->MODER &= ~(3U << 2*6);
    GPIOC->MODER |= (1U << 2*6);
}
void onboardLed_TurnOn(){
    /* Turn on LED */
    GPIOC->ODR |= (1U << 6);
}
void onboardLed_TurnOff(){
    /* Turn on LED */
    GPIOC->BRR |= (1U << 6);
}
void onboardLed_Toggle(){
    /* Turn on LED */
    GPIOC->ODR ^= (1U << 6);
}


//INITILIZE BUTTON CONNECTED TO PA5 PIN

void button_set(){
    /* Enable GPIOA clock */
    RCC->IOPENR |= (1U << 0);
	//Set PA5 as input
	GPIOA->MODER &= ~(3U << 2*5);
}
//RETURNS 1 IF BUTTONS PRESSED
int button_read(){
	int b = ((GPIOA->IDR >>5 ) & 0X1);
	if(b)
		return 0;
	else return 1;
}

//BUTTON WITH EXTERNAL INTERRUPTS
void button_interrupt(){
	//Set PA5 as input
	EXTI->RTSR1 |= (1U << 5);
	EXTI->EXTICR[5] |= (1U << 8*5);
	EXTI->IMR1 |= (1U << 5);

	NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}

//UART MEVZULARI
void USART2_IRQHandler(void){
	uint8_t data = (uint8_t)USART2->RDR;
	uart_tx(data);
}


void uart_tx(uint8_t c){

	USART2->TDR = (uint16_t)c;
	while(!(USART2->ISR & (1U << 6)));
}

uint8_t uart_rx(void){

	while(!((USART2->ISR) & (1U << 5)));

	return (uint8_t)USART2->RDR;

	//RXNE AUTOMATICALLY CLEARED WHEN ITS READ
}


void UART_init(uint32_t baud){
	RCC->IOPENR |= (1U << 0);
	RCC->APBENR1 |= (1U << 17); //	RCC->APBENR1 |= (1U << RCC_APBENR1_USART2EN);

	//SET PA2 AS ALTERNATE FUNCTION(AF1)
	GPIOA->MODER &= ~(3U << 2*2);
	GPIOA->MODER |= (2U << 2*2);
	GPIOA->AFR[0] &= ~(0XFU << 4*2);
	GPIOA->AFR[0] |= (1U << 4*2);  //0001 for AF1

	//SET PA3 AS ALTERNATE FUNCTION(AF1)
	GPIOA->MODER &= ~(3U << 2*3);
	GPIOA->MODER |= (2U << 2*3);
	GPIOA->AFR[0] &= ~(0XFU << 4*3);
	GPIOA->AFR[0] |= (1U << 4*3);  //0001 for AF1

	//SETUP UART
	USART2->CR1 = 0;
	USART2->CR1 |= (1 << 3); //TE
	USART2->CR1 |= (1 << 2); //RE
	USART2->CR1 |= (1 << 5); //RXNEIE

	USART2->BRR = (uint16_t)(SystemCoreClock / baud);

	USART2->CR1 |= (1 << 0); //UE

	NVIC_SetPriority(USART2_IRQn, 1);
	NVIC_EnableIRQ(USART2_IRQn);
}
