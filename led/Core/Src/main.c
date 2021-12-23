/*
* main.c
*
* author: Aylin Nisa Üneş-Deniz İkitemur-Mustafa Alkan
*/
#include "stm32g0xx.h"
void delay_ms(volatile unsigned int);
int main(void) {
SystemCoreClockUpdate();
 /* Enable GPIOC clock */
 RCC->IOPENR |= (1U << 2);
 /* Enable GPIOA clock */
 RCC->IOPENR |= (1U << 0);
 //Set up PB5 as output
    GPIOB->MODER &= ~(3U << 2*5);
    GPIOB->MODER |= (1U << 2*5);
 /* Turn on LED */
 GPIOB->ODR &=(0U << 5);
 int Start = SysTick->VAL;
 delay_ms(10000);
 int Stop = SysTick->VAL;
 unsigned int Delta = 0x00FFFFFF&(Start-Stop);
 while(1) {
 delay_ms(10000);
 /* Toggle LED */
 GPIOB->ODR &=(0U << 5);
 }
 return 0;
}
void delay_ms(volatile unsigned int s){
for(int i=s; i>0; i--){
SysTick_Config(SystemCoreClock / 1000);
}
}
