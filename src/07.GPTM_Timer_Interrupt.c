/*
 * 07.GPTM_Timer_Interrupt.c
 *
 *  Created on: 15-Dec-2019
 *      Author: black_Pearl
 */

#include<stm32f4xx.h>

int main(){
	RCC->AHB1ENR |= 0x1;
	GPIOA->MODER |= 0x400;

	RCC->APB1ENR |=0x1;
	TIM2->PSC = 16000-1;
	TIM2->ARR = 1000-1;		// 1 Hz frequency
	TIM2->CNT = 0;
	TIM2->CR1 = 1;		// Timer ON
	TIM2->DIER = 0x1;	// Interrupt Enable

	NVIC_EnableIRQ(TIM2_IRQn);

	while(1);

	return 0;
}

void TIM2_IRQHandler(void){
	TIM2->SR = 0;		// Updating Interrupt flag
	GPIOA->ODR ^= (1<<5);

}
