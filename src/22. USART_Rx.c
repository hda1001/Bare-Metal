/*
 * 21. USART_Rx.c
 *
 *  Created on: 14-Dec-2019
 *      Author: black_Pearl
 */


// USART 2 APB1EN
// PA3 USART2 RX

#include "stm32f4xx.h"                  // Device header

char USART_read(void);
void USART2_Init(void);
void delay(int var);
void led_blink(char ch);

char ch;
int data;

int main(void){

	RCC->AHB1ENR |= 1;		// GPIOA Enable
	GPIOA->MODER &= ~(3<<(2*5));		//GPIO MODE Settings
	GPIOA->MODER |= (1<<2*5);				// GPIO OUTPUT MODE
	GPIOA->OSPEEDR  &= ~(3 << (2*5));	// GPIO Pin Speed
	GPIOA->OSPEEDR  |= (3 << (2*5));	// FAST MODE
	GPIOA->OTYPER &= ~(1 << 5);			// GPIO OTYPE
	GPIOA->PUPDR &= ~(3 << (2*5));	// PUPD

	USART2_Init();

	while(1){
		ch = USART_read();
		led_blink(ch);
	}
}

void USART2_Init(void){
	RCC->APB1ENR |= 0x20000;	//(1<<17);		// USART2 ENABLE
	RCC->AHB1ENR |= 1;				//(1<<0);			// GPIOA Enable

	GPIOA->AFR[0] |= 0x7000;	// PA3 AF7 RX
	GPIOA->MODER |= 0x0080;		// PA2 Set

	USART2->BRR = 0x008B;			// 115200 @ 16 MHz
	USART2->CR1 = 0x0024;			// RE Enable
	USART2->CR1 |= 0x2000;		// UE Enable
	NVIC_SetPriority(USART2_IRQn, 5);	// Highest priority
	NVIC_EnableIRQ(USART2_IRQn);

}

//char USART_read(void){
//	// Check wthether DR is empty or not || TXE bit of SR ||
//	while(!(USART2->SR & 0x0020));		// Wait till RXNE is 1
//	data = USART2->DR;
//	return (USART2->DR);
//}
void USART2_IRQHandler(void){
	while(!(USART2->SR & 0x0020));
	data = (USART2->DR && 0xFF);
}

void led_blink(char ch){
	if(ch%16 != 0){
		//GPIOA->ODR ^= (1 << 5);
		GPIOA->BSRRL = 0x20;			// 5 bit		// 0x20
		delay(100);
		GPIOA->BSRRH = ((0x20));				//0x002
		delay(100);
	}
}

void delay(int var){
	for(int i=0; i< 3195*var; i++);
}

