/*
 * 002. ADC_Sensor_USART.c
 *
 *  Created on: 15-Dec-2019
 *      Author: black_Pearl
 */

#include <stm32f4xx.h>
#include <stdio.h>

void USART2_Init(void);
int data =0;
int voltage;
float celcious;
int USART2_Write(int ch);


int main(){
	RCC->AHB1ENR |= 1;

	RCC->APB1ENR |= 1;
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	TIM2->CNT =0;
	TIM2->CCMR1 = 0x6800;
	// Timer 2 / Compare 2/ CC2 configured / toggle
	// CCR2 TIM2 = CNT toggle
	TIM2->CCER = 0x10;		// CC2 Enable
	TIM2->CCR2 = 50-1;// check
	TIM2->CR1 = 1;			// Enable Timer

	// ADC Setup
	RCC->APB2ENR |= 0x100;
	ADC->CCR |= 0x800000;	// bit 22 (1<<22)
	ADC->CCR &= ~(0x400000); //VBATE nust be disabled for temp sensor


	ADC1->SMPR1 =0x4000000;	// Sampling time minimum 10usec
	ADC1->SQR3 = 18;		// Channel Number
	ADC1->CR2 =0x13000000; // Start Conversion
	ADC1->CR2 |=1;

	USART2_Init();
	printf("ST32F4 Temperature \n\r: ");
	while(1){
		while(!(ADC1->SR));
		data = ADC1->DR;
		voltage = (double)data/4095 * 3.3;
		celcious = (((voltage - 0.76)/0.0025)+25);
		printf("%d, %0.2d \370C\r\n", data, celcious);
	}
	return 0;
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
struct __FILE{int handle;};
//	FILE __stdin   = {0};
	FILE __stdout  = {1};
//	FILE __stderr  = {2};

	int fputc(int c, FILE *f){
	return USART2_Write(c);
}

int USART2_Write(int ch){
	while(!(USART2->SR & 0x0080));
	USART2->DR = ch;
	return ch;
}

