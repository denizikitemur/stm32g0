/*
 * main.c
 *
 * author: Deniz İkitemur
 *
 * description: Using a state machine blink the external LED at different intervals. Assign each speed to a mode, and attach a button to cycle through the modes.
 */

#include "stm32g0xx.h"

#define LEDDELAY1    3200000
#define LEDDELAY2	 1600000
#define LEDDELAY3    800000
#define LEDDELAY4    160000

void delay(volatile uint32_t);


int main(void) {

    /* Enable GPIOA clock */
    RCC->IOPENR |= (1U << 0);

    /* Enable GPIOB clock */
    RCC->IOPENR |= (1U << 1);

    //Set up PB5 as output
    GPIOB->MODER &= ~(3U << 2*5);
    GPIOB->MODER |= (1U << 2*5);

    //Set PA5 as input
    GPIOA->MODER &= ~(3U << 2*5);

    while(1) {


    	int i = 0;

    				if (((GPIOA->IDR & (1U << 5)) == 0x20) && (i == 0)){ //0010 0000
    					for(;;){
    						GPIOB->ODR &=(0U << 5); // mode 0
    						if((GPIOA->IDR & (1U << 5)) == 0x20){
    							i++;
    							goto a0;
    						}

    					}
    				}
    				a0:

    	    	    if (((GPIOA->IDR & (1U << 5)) == 0x20) && (i == 1)){ //0010 0000
    	    	    	for(;;){

    	    	    	GPIOB->ODR |= (1U << 5); // mode 1
    	    	    	delay(LEDDELAY1);
    	    	    	GPIOB->ODR &=(0U << 5);
    	    	    	delay(LEDDELAY1);
    	    	    	if((GPIOA->IDR & (1U << 5)) == 0x20){
    	    	    		i++;
    	    	    		goto a1;
    	    	    	}

    	    	    	}
    	    	    }
    	    	    a1:


    	    	    if ((GPIOA->IDR & (1U << 5)) == 0x20 && i == 2){ //0010 0000
    	    	        for(;;){

    	    	        GPIOB->ODR |= (1U << 5); // mode 2
    	    	        delay(LEDDELAY2);
    	    	        GPIOB->ODR &=(0U << 5);
    	    	        delay(LEDDELAY2);
    	    	        if((GPIOA->IDR & (1U << 5)) == 0x20){
    	    	        	i++;
    	    	            goto a2;
    	    	           }

    	    	           }
    	    	         }
    	    	       a2:

    	    	    if ((GPIOA->IDR & (1U << 5)) == 0x20 && i == 3){ //0010 0000
    	    	        for(;;){

    	    	        	GPIOB->ODR |= (1U << 5); //mode 3
    	    	        	delay(LEDDELAY3);
    	    	        	GPIOB->ODR &=(0U << 5);
    	    	        	delay(LEDDELAY3);
    	    	        	if((GPIOA->IDR & (1U << 5)) == 0x20){
    	    	        	i++;
    	    	        	goto a3;
    	    	        	    	    	}
    	    	        	    	    }
    	    	    }
    	    	    a3:


    	    	    if ((GPIOA->IDR & (1U << 5)) == 0x20 && i == 4){ //0010 0000
    	    	        for(;;){

    	    	        	GPIOB->ODR |= (1U << 5); // mode 4
    	    	        	delay(LEDDELAY4);
    	    	        	GPIOB->ODR &=(0U << 5);
    	    	        	delay(LEDDELAY4);
    	    	        	if((GPIOA->IDR & (1U << 5)) == 0x20){
    	    	        	i++;
    	    	        	goto a4;
    	    	        	    	    	}
    	    	        	    	    }
    	    	    }
    	    	    a4:


    	    	    if ((GPIOA->IDR & (1U << 5)) == 0x20 && i == 5){ //0010 0000
    	    	        for(;;){

    	    	        	GPIOB->ODR |= (1U << 5); // mode 5
    	    	        	if((GPIOA->IDR & (1U << 5)) == 0x20){
    	    	        	i++;
    	    	        	goto a5;
    	    	        	    	    	}
    	    	        	    	    }
    	    	    }
    	    	    a5:
		    i=0;


    	 delay(600000); //duration for press and back for the button

    }//while(1)

    return 0;
}//main funct

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}