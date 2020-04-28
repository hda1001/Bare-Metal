/*
 * 10. Led_Interrupt.c
 *
 *  Created on: 13-Dec-2019
 *      Author: black_Pearl
 */

#include<stm32f4xx.h>
void systickDelay(int n);
int main(void){
//	__disable_irq();	// disabling interupt
	RCC->AHB1ENR|= 0x1;
	RCC->AHB1ENR|= 0x4;
	RCC->APB2ENR |= 0x4000;
	GPIOA->MODER |= 0x400;

	GPIOC->MODER |= 0;

	EXTI->IMR = 0x2000;
	EXTI->RTSR = 0x2000;
	SYSCFG->EXTICR[3] = 0x20;

	NVIC_EnableIRQ(EXTI15_10_IRQn);
	while(1);

//	__enable_irq();
	return 0;
}

void EXTI15_10_IRQHandler(void){
	uint16_t del = (SystemCoreClock/1000000)/3;
	while((GPIOC->IDR)== 1){
		GPIOA->ODR = (1<<5);
		for(int i=0; i< (1000000*del); i++);
		GPIOA->ODR = (0<<5);
		for(int i=0; i< (100*del); i++);
		EXTI->PR = 0x2000;		// Clearing the pending Interrupt
	}
}

void systickDelay(int n){
//	DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STOP | DBGMCU_STANDBY, ENABLE);

	while(n>0){
	SysTick->LOAD = 16000000-1; 	// Reload value: 10msec = val x 62.5 n
	SysTick->VAL = 0;		// current value is 0
	SysTick->CTRL = 0x5;
	n--;
	while((SysTick->CTRL & (1<<16))==0);
	}
	SysTick->CTRL = 0;		// Timer Disable
}
