/*
 * 4. GPTM_Compare.c
 *
 *  Created on: 12-Dec-2019
 *      Author: black_Pearl
 */

#include<stm32f4xx.h>

int main(){
	RCC->AHB1ENR = 0x1;
	GPIOA->MODER |= 0x800;		// ALT Function

	// Timer 2 Channel 1 === PA5-->> AF1 for Timer 2
	GPIOA->AFR[0] = 0x100000;	// AF1

	RCC->APB1ENR |= 0x1;
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	TIM2->CCMR1 = 0x30;		// Toggle mode when TIM2->CNT = TIM2-> CCR1
	TIM2->CCR1 = 0;
	TIM2->CCER = 1;		// Enable ch1 compare mode
	TIM2->CNT = 0;		// Clear Counter
	TIM2->CR1 = 1;		// Enable TIM2
	return 0;
}
