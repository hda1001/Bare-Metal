/*
 * 003. ADC_LM35.c
 *
 *  Created on: 16-Dec-2019
 *      Author: black_Pearl
 */

#include <stm32f4xx.h>
#include <stdio.h>


int data =0;
int voltage;
float temp;
void ADC1_Init(void);
uint32_t getADCValue();

int main(){
	RCC->AHB1ENR |= 0x1;	// Clock GPIOA
	GPIOA->MODER |= 0XC;	// setting analog Mode of PA1
	ADC1_Init();
	uint32_t adcVal;
	while(1){
		adcVal = getADCValue();
		temp = (adcVal * 5) / 4096;
		temp *= 100;
	}

	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0XC;	// setting analog Mode of PA1
//	GPIOA->MODER |= 0x20;	// PA2 as ALT Function

//	RCC->APB1ENR |= 1;
//	TIM2->PSC = 1600-1;
//	TIM2->ARR = 10000-1;
//	TIM2->CNT =0;
//	TIM2->CCMR1 = 0x6800;
	// Timer 2 / Compare 2/ CC2 configured / toggle
	// CCR2 TIM2 = CNT toggle
//	TIM2->CCER = 0x10;		// CC2 Enable
//	TIM2->CCR2 = 50-1;// check
//	TIM2->CR1 = 1;			// Enable Timer

	// ADC Setup
//	RCC->APB2ENR |= 0x100;
//	ADC->CCR |= 0x800000;	// TSVRef bit 22 (1<<22)
//	ADC->CCR &= ~(0x400000); //VBATE nust be disabled for temp sensor
//
//
//	ADC1->SMPR1 =0x4000000;	// Sampling time minimum 10usec
//	ADC1->SQR3 = 18;		// Channel Number
//	ADC1->CR2 =0x13000000; // Start Conversion
//	ADC1->CR2 |=1;
//
//	while(1){
//		while(!((ADC1->SR) & 0x2) == 0);
//		data = ADC1->DR;
//		voltage = (double)data/4095 * 3.3;
//		temp = (((voltage - 0.76)/0.0025)+25);
//	}
	return 0;
}

//	void ADC1_Init(void){
//	RCC->APB2ENR |= (1<<8);	// Enable ADC1
//		RCC->CFGR |= (0b110 << 13);	// High speed by 8
//		ADC1->SMPR2 |= (0b110 << 0); //sampling time 84 cycle
//		ADC1->CR2 =0x13000000;
//			ADC1->CR2 |= (1<<0); //ADC ON
//}

uint32_t getADCValue(){

	ADC_Cmd(ADC1, ENABLE);
	while(!(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) == 0);
	uint32_t adcVal = ADC_GetConversionValue(ADC1);
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	return adcVal;


//	ADC1->SQR3 |= (0<<0);
//	ADC1->CR2 |= (1<<0);	//Enable ADC
//	while(!(ADC1->SR & 0x2));
//	uint32_t adcVal = ADC_GetConversionValue;
//	return adcVal;
}


void ADC1_Init(){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 16, ADC_SampleTime_84Cycles);
	ADC_VBATCmd(ENABLE);
//	ADC_EOCOnEachRegularChannelCmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
	ADC_ContinuousModeCmd(ADC1, ENABLE);
}
