#include <stm32f4xx.h>
#include <stdlib.h>
#include <stdio.h>

#define DHT11	PA1;

int main(void){
	RCC->AHB1ENR = 0x1;		// GPIOA
	GPIOA->MODER |= 0x400;	// Output mode
	while(1){
			GPIOA->ODR ^= (1<<5);
		}

	return 0;
}

void Request()			/* Microcontroller send request */
{
	RCC->AHB1ENR = 0x1;		// GPIOA
	GPIOA->MODER = 	/* set to low pin */
	timer_delay20ms();	/* wait for 20ms */
	DHT11 = 1;		/* set to high pin */
}

void ms_delay(int num){
	for(int i=0; i<1000*num; i++);
}
void us_delay(int num){
	for(int i=0; i<1*num; i++);
}

//	RCC->APB1ENR |= 0x20000;	//(1<<17);		// USART2 ENABLE
//	GPIOA->AFR[0] = 0x700;
//	USART2->CR1 = 0x0008;			// TE Enable
//	USART2->CR1 |= 0x2000;		// UE Enable
//
//	USART_InitTypeDef *uart;
//	uart->USART_BaudRate = 0x683;
//	uart->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	uart->USART_Mode = USART_Mode_Tx;
//	uart->USART_Parity =USART_Parity_No;
//	uart->USART_StopBits = USART_CR2_STOP_1;
//	uart->USART_WordLength = USART_WordLength_8b;
//	USART_Init(USART2, &uart);
//			while(!(USART2->SR & 0x0080));
//			USART2->DR = 0x65;
