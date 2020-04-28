#include "stm32f4xx.h"                  // Device header
#include <string.h>
#include <stdio.h>
#include <stdint.h>

char USART_read(void);
void USART2_Init(void);
void delay(int var);
void led_blink(char ch);

char ch;
int data[5];
static int i;

//extern void initialise_monitor_handles();
int main(void){

	RCC->AHB1ENR |= 1;		// GPIOA Enable
	GPIOA->MODER |= (1<<2*5);				// GPIO OUTPUT MODE
	GPIOA->OSPEEDR  |= (3 << (2*5));	// FAST MODE

	USART2_Init();

	while(1){
		data[i] = USART_read();
		i++;
		if(data[0] != 1){
			i=0;
		}
		if(strlen(data) == 5){
			i=0;

		}
		led_blink(ch);
	}
}

void USART2_Init(void){
	RCC->APB1ENR |= 0x20000;	//(1<<17);		// USART2 ENABLE
	RCC->AHB1ENR |= 1;				//(1<<0);			// GPIOA Enable

	GPIOA->AFR[0] |= 0x7000;	// PA3 AF7 RX
	GPIOA->MODER |= 0x0080;		// PA2 Set

	USART2->BRR = 0x00BB;			// 115200 @ 16 MHz
	USART2->CR1 = 0x0004;			// RE Enable
	USART2->CR1 |= 0x2000;		// UE Enable

}

char USART_read(void){
	// Check wthether DR is empty or not || TXE bit of SR ||
	while(!(USART2->SR & 0x0020));		// Wait till RXNE is 1
	return (USART2->DR);
}

//void led_blink(char ch){
//	if(ch%16 != 0){
//		//GPIOA->ODR ^= (1 << 5);
//		GPIOA->BSRR = 0x20;			// 5 bit		// 0x20
//		delay(100);
//		GPIOA->BSRR = ((0x20)<<16);				//0x002
//		delay(100);
//	}
//}

void delay(int var){
	for(int i=0; i< 3195*var; i++);
}

