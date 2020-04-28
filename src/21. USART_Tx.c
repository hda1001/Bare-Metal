/*
 * 20. USART.c
 *
 *  Created on: 14-Dec-2019
 *      Author: black_Pearl
 */

// USART 2 APB1EN
// PA2 USART2 TX & PA3 USART2 RX
#include "stm32f4xx.h"                  // Device header

void USART_write(int ch);
void USART2_Init(void);
void delay(int var);

int main(void){
	USART2_Init();
	while(1){
		USART_write('H');
		USART_write('I');
		USART_write('\n');
		USART_write('\r');
		delay(100);
	}
}

void USART2_Init(void){
	RCC->APB1ENR |= 0x20000;	//(1<<17);		// USART2 ENABLE
	RCC->AHB1ENR |= 1;				//(1<<0);			// GPIOA Enable

	GPIOA->AFR[0] |= 0x0700;	// PA2 AF7
	GPIOA->MODER |= 0x0020;		// PA2 Set

	USART2->BRR = 0x0683;			// 9600 @ 16 MHz
	USART2->CR1 = 0x0008;			// TE Enable
	USART2->CR1 |= 0x2000;		// UE Enable

}

void USART_write(int ch){
	// Check wthether DR is empty or not || TXE bit of SR ||
	while(!(USART2->SR & 0x0080));
	USART2->DR = (ch & 0xFF);

}

void delay(int var){
	for(int i=0; i< 3195*var; i++);
}


