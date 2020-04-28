/*
 * GPTM_Compare_Mode.c
 *
 *  Created on: 13-Dec-2019
 *      Author: black_Pearl
 */


/*
 * used for counting number of events
 * or count the number of rising edge or falling edge
 */

/*
 * Capturing the toggle rate of PA5 and PA6 will be input capture
 * pin
 */
#include<stm32f4xx.h>

int timeStamp =0;
int main(void){

	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x800;		// PA5 as ALT Function
	GPIOA->AFR[0] |= 0x100000;	// AF1 in PA5

	// TIM2 config in Compare mode
	RCC->APB1ENR |= 1;
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	TIM2->CNT = 0;
	TIM2->CCMR1 = 0x30; 	// Set output to toggle on match
		// Configured as output mode
	TIM2->CCR1 = 0;			// Set Match value
	TIM2->CCER = 1;		// Capture Enable || Output mode
	TIM2->CR1 = 1;		// Enable TIM2


	//TIM3 config in Input Capture mode
	// PA6--->> AF2 ---->> TIM3_CH1
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x2000;		// PA6 as ALT Function
	GPIOA->AFR[0]|= 0x2000000;	// AF2 in PA6

	RCC->APB1ENR |= 2;		// TIM3 config
	TIM3->PSC = 16000-1;
	TIM3->CCMR1 = 0x41;		// configured as input
	TIM3->CCER = 1;			// Capture Enable
	TIM3->CR1 =1;

	// wait until input edge is captured
	while(1){
		while(TIM3->SR & 2);
		timeStamp = TIM3->CCR1;
	}
	return 0;
}
