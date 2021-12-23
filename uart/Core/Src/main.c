#include "stm32g0xx.h"
static volatile uint32_t c = 0;

void SysTick_Handler(void)
{
    if(c > 0)
    {
        --c;
    }
}
void UART_init(uint32_t baud){ /*init UART */
    RCC->IOPENR |= (1U << 0); /* enable A */
    RCC->APBENR1 |= (1U << 17); /*enable USART2 */
    /*   set PA2 as alternate function mode */
    GPIOA->MODER &= ~(3U << 2*2);
    GPIOA->MODER |= (2U << 2*2);
    /* choose AF1 from the mux */
    GPIOA->AFR[0] &= ~(0xFU << 4*2);
    GPIOA->AFR[0] |= (1U << 4*2);
    /* setup PA3 as alternate function mode */
    GPIOA->MODER &= ~(3U << 2*3);
    GPIOA->MODER |= (2U << 2*3);
    /* choose AF1 from the mux */
    GPIOA->AFR[0] &= ~(0xFU << 4*3);
    GPIOA->AFR[0] |= (1U << 4*3);
    /* setup UART2 */
    /* reset UART2 CR1 */
    USART2->CR1 = 0;
    USART2->CR1 |= (1U << 3); /* TE */
    USART2->CR1 |= (1U << 2); /* RE */
    USART2->BRR = (uint16_t)(SystemCoreClock / baud);
    USART2->CR1 |= (1U << 0); /* UE */



}
void uart_tx(uint8_t c){ /* setting transmission of data */
    USART2->TDR = (uint16_t)c; /* transmit data Register */
    while (!(USART2->ISR & (1U << 6)));
}
uint8_t uart_rx(void){ /* setting serceiving of data */
    uint8_t data = (uint8_t)USART2->RDR;
    return data;
}

void printChar(int fd,char *buf,int length){
	(void) fd;
	for (int i=0;i<length;++i){
		uart_tx(buf[i]);
	}

}

void _print(char *buf){
	int length=0;
	while(buf[length++]!='\0');
	printChar(0,buf,length);
}



int main(void) {
	SysTick_Config(SystemCoreClock / 1000);
    UART_init(9600);

    while(1) {
    	_print("hello world from usart2\n\r");
     }
    return 0;
}
