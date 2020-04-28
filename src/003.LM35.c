/*
 * 003.LM35.c
 *
 *  Created on: 16-Dec-2019
 *      Author: black_Pearl
 */

#include <stm32f4xx.h>


uint16_t data;
uint16_t voltage;
uint16_t temp;

int main(){
	RCC->AHB1ENR |= 0x1;	// Clock GPIOA
	GPIOA->MODER |= 0X3;	// setting analog Mode of PA0


	RCC->APB2ENR |= 0x100;	// ADC Enable
	ADC1->CR1 |= 2000000;	// Resolution 10 bit
	ADC->CCR |= 0x800000;	// TSVRef bit 22 (1<<22)
	ADC->CCR &= ~(0x400000); //VBATE nust be disabled for temp sensor

	ADC1->SMPR1 =0x2;	// 15 cycles
	ADC1->SQR3 = 0;		// Channel Number
//	ADC1->CR2 =0x13000000; // Start Conversion
	ADC1->CR2 |=1;			// ADC ON

	while(1){
		while(!((ADC1->SR) & 0x2));
		data = ADC1->DR;
//		voltage = (double)data/4095 * 3.3*10;
//		temp = (((voltage - 0.76)/0.0025)+25);
	}
	return 0;
}
