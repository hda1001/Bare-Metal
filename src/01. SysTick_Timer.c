/*
 * SysTick_Timer.c
 *
 *  Created on: 10-Dec-2019
 *      Author: black_Pearl
 */


#include "stm32f4xx.h"                  // Device header
#include "stdio.h"
int main(void){
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400;
	//int n=10000;
	// generating 200msec delay
	// Configure SysTick

	SysTick->LOAD = 320000 -1; 	// 200m = val x 62.5 n
	SysTick->VAL = 0;		// current value is 0
	SysTick->CTRL = 5;

	while(1){
		// check if count flag is set
		while(!(SysTick->CTRL & 0x10000));
			GPIOA->ODR ^= 0x20;
	}
}
