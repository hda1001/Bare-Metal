/*
 * GPTM.c
 *
 *  Created on: 10-Dec-2019
 *      Author: black_Pearl
 */


#include<stm32f4xx.h>

int main(void){
//	DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STOP | DBGMCU_STANDBY, ENABLE);
	// creating 1 hz (1 sec) timer to toggle the led

	RCC->AHB1ENR |= 0x1;
	GPIOA->MODER |= 0x400;

	RCC->APB1ENR |=(1<<4);

		TIM6->PSC = (4500-1);
		TIM6->ARR = 10000-1;	// 10000 division 10000 = 1Hz
		TIM6->CNT =0;		// Clear timer counter
		TIM6->CR1 = 0x1;		// TIM2 ENR

		TIM6->DIER = (1<<0);
//		SCB->SCR |=1;
		NVIC_EnableIRQ(TIM6_DAC_IRQn);
		while(1){
//			while(!(TIM2->SR & 0x1) == 0){
//				TIM2->SR &= ~1;		// clear SR first
//				GPIOA->ODR ^= (1<<5);
//			}
		}
}

void TIM6_DAC_IRQHandler(){
	TIM6->SR = 0;		// clear Interrupt
	GPIOA->ODR ^= (1<<5);
}
