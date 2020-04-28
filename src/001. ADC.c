/*
 * 001. ADC.c
 *
 *  Created on: 15-Dec-2019
 *      Author: black_Pearl
 */

#include<stm32f4xx.h>


int analogValue =0;

int main(){
	RCC->AHB1ENR |= 0x1;	// Clock GPIOA
	GPIOA->MODER |= 0XC;	// setting analog Mode of PA1
//	GPIOA->MODER |= 0x20;	// PA2 as ALT Function

	RCC->APB2ENR |= 0x100;	// ADC clock channel
	ADC1->CR2 |= 0;			// Disabling the ADC
	ADC1->SQR3 = 1;
	ADC1->CR2 = 1;			// Enabling ADC


	while(1){
		ADC1->CR2 |= 0x40000000;	// bit 30	(1<<30);
		while(!(ADC1->SR & 0x2));	// wait for the end of conversion
		analogValue = ADC1->DR;
	}

	return 0;
}
