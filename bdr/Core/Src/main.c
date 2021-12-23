#include "stm32g0xx.h"
#include<stdio.h>
void delay(volatile uint32_t);
#define LEDDELAY 10UL
#define LEDDELAY1 8000UL
volatile uint32_t millis;
uint32_t dakika2[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x47, 0x7F, 0x6F};
uint32_t kontrol[4]  = {0x10, 0x20, 0x40, 0x80};
uint32_t dakika1[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x47, 0x7F, 0x6F};
uint32_t saniye2[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x47, 0x7F, 0x6F};
uint32_t saniye1[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x47, 0x7F, 0x6F};
int ctrl;
volatile int i=2;
volatile int j=4;
volatile int k=5;
volatile int l=9;

 void systickinit(uint32_t tick){
	 SysTick->CTRL = 0;
	 SysTick->LOAD = tick - 1;
	 SysTick->VAL  = 0;
	 SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	 SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	 SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	 NVIC_EnableIRQ(SysTick_IRQn);
	 NVIC_SetPriority (SysTick_IRQn,0);
	}


        void SysTick_Handler(void) {
        	static int counter;
        	l--;
        	if(l == 0){
        		l=9;
        		j--;
        	}
        	else if(j == 0 && l == 0){
        		l=9;
        		j=5;
        		k--;
        	}


	}

void segment1(uint32_t x){
	GPIOB->ODR &= 0x00;
	GPIOA->ODR |= ~(kontrol[0]);
	GPIOA->ODR &= ~(kontrol[0]);
	GPIOB->ODR &= dakika2[x];
	GPIOB->ODR |= dakika2[x];
}

void segment2(uint32_t x){
	GPIOB->ODR &= 0x00;
	GPIOA->ODR |= ~(kontrol[1]);
	GPIOA->ODR &= ~(kontrol[1]);
	GPIOB->ODR &= dakika1[x];
	GPIOB->ODR |= dakika1[x];
	GPIOB->ODR |=0x80;
}
void segment3(uint32_t x){
	GPIOB->ODR &= 0x00;
	GPIOA->ODR |= ~(kontrol[2]);
	GPIOA->ODR &= ~(kontrol[2]);
	GPIOB->ODR &= saniye2[x];
	GPIOB->ODR |= saniye2[x];
}

void segment4(uint32_t x){
	GPIOB->ODR &= 0x00;
	GPIOA->ODR |= ~(kontrol[3]);
	GPIOA->ODR &= ~(kontrol[3]);
	GPIOB->ODR &= saniye1[x];
	GPIOB->ODR |= saniye1[x];
}

void baslangic(){
	segment1(0);
	segment2(0);
	segment3(0);
	segment4(0);

}


void display(){
	segment1(i);
	delay(LEDDELAY1);
	segment2(j);
	delay(LEDDELAY1);
	segment3(k);
	delay(LEDDELAY1);
	segment4(l);
	delay(LEDDELAY1);
		}








void delay(volatile uint32_t s){
	for(;s>0; s--);
}


int main(void){
	RCC->IOPENR |=3U; // 3U=0011; RCC->IOPENR = xxxx...xx11;
	GPIOA->MODER &= ~(0xFF<<8);// GPIOA->MODER |
	GPIOA->MODER |= (0x55<<8); // 0101 0101 << 8 = 0101
	GPIOA->MODER &= ~(0xF); //xxxx...0000
	GPIOA->MODER |=  0x1  ;// xxxx...0001 buton i�in PA1 ayarland�
	GPIOB->MODER |= (0xFFFF);
	GPIOB->MODER &= (0x5555);


	while(1){

	display();

	}



	return 0;
}


