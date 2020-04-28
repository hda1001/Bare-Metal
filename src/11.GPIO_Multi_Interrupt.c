/*
 * 11.GPIO_Multi_Interrupt.c
 *
 *  Created on: 14-Dec-2019
 *      Author: black_Pearl
 */
#include<Stm32f4xx.h>

int count1 = 0;
int count2 = 0;

int main(){
	RCC->AHB1ENR |= 0x7;
	RCC-> APB2ENR |= 0x4000;

	// for PC10 configuration
	GPIOA->MODER |= 0x400;
	SYSCFG->EXTICR[3] =0x20;
	EXTI->IMR |= 0x2000;
	EXTI->FTSR = 0x2000;

	// For PB10 configuration
	GPIOB->OTYPER |= 0x400;
	GPIOB->PUPDR |= (1<<10);
	SYSCFG->EXTICR[2] = 0x100;
	EXTI->IMR |= 0x400;
	EXTI->FTSR |= 0x400;

	NVIC_EnableIRQ(EXTI15_10_IRQn);

//	NVIC_InitTypeDef NPR;
//	NPR.NVIC_IRQChannel = EXTI15_10_IRQn;
//	NPR.NVIC_IRQChannelCmd = ENABLE;
//	NPR.NVIC_IRQChannelPreemptionPriority = 0; // Highest pre-emption priority
//	NPR.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&NPR);
//
//	NVIC_SetPriority(EXTI15_10_IRQn,2);

	return 0;
}

void EXTI15_10_IRQHandler(void){
	if(EXTI->PR & (0x2000)){		// for PC13
		count1++;
		GPIOA->ODR = (1<<5);
		for(int i=0; i<1000000; i++);
		GPIOA->ODR = (0<<5);
		for(int i=0; i<1000000; i++);
		EXTI->PR |= 0x2000;
	}

	if(EXTI->PR & (0x400)){		// for PC13
		count2++;
		GPIOA->ODR = (1<<5);
		for(int i=0; i<1000000; i++);
		GPIOA->ODR = (0<<5);
		for(int i=0; i<1000000; i++);
		EXTI->PR |= 0x400;
	}
}
