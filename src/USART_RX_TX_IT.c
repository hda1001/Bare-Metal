/*
 * USART_RX_TX_IT.c
 *
 *  Created on: 03-Apr-2020
 *      Author: black_Pearl
 */

#include<stm32f4xx.h>

int main(){
	RCC->APB1ENR = 0x20000;	//(1<<17);		// USART2 ENABLE
	RCC->AHB1ENR = 0x5;		//(101<<0);			// GPIOA & GPIOC Enable
//	RCC->APB2ENR = (1<<14);		// Sysconfig Enable

	GPIOA->MODER |= 0x00A0;		// PA2 Set(TX) and PA3(RX)

	GPIOA->MODER |= (1<<10);	// PA5
	GPIOA->MODER |= (1<<8);		// PA4
	GPIOA->MODER |= 0x05;		// PA0 PA1
	GPIOC->MODER = (00 << 26);
	GPIOC->PUPDR = (2<< 26);
	GPIOA->AFR[0] |= 0x7700;	// PA2 PA3 AF7


	USART2->BRR = 0x0683;			// 9600 @ 16 MHz
	USART2->CR1 = 0x2024;			// RXNE and TE, RE Enable
//	USART2->CR1 |= 0x2000;			// UE Enable
	NVIC_SetPriority(USART2_IRQn, 5);	// Highest priority
	NVIC_EnableIRQ(USART2_IRQn);

}

uint8_t data;

void USART2_IRQHandler(void){
	while(!(USART2->SR & 0x20)){	}
		data = (USART2->DR & 0xFF);
}
