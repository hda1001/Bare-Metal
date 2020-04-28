/*
 * 9. GPIO_Interrupt.c
 *
 *  Created on: 13-Dec-2019
 *      Author: black_Pearl
 */

#include<stm32f4xx.h>

int main(void){
	RCC->AHB1ENR |= 0x5;
	RCC->APB2ENR |= 0x4000;
	GPIOA->MODER |= 0x400;
	GPIOA->OTYPER |= 0;

	GPIOC->MODER |= 0;

	EXTI->IMR = 0x2000;
	EXTI->RTSR = 0x2000;
	SYSCFG->EXTICR[4] |= 0x20;
	NVIC->ISER[1] = (1<<8);
	NVIC->IP[10] = 	(0xF0);			// EXTI15_10_IRQHandler ==> Position is 40 and we give priority according to our need

	//  40/4	= 10. So IP[10] and 40%4 =0. 0 block and lower nibble is useless, only upper nibble is useful

	return 0;
}

void EXTI15_10_IRQHandler(void){
	while(((GPIOC->IDR)>>13)== 0){
		GPIOA->ODR ^= (1<<5);
		for(int i=0; i<1000000; i++);
	}
	if(EXTI->PR & (1>> 13)){
		EXTI->PR |= 0x2000;
	}
}
