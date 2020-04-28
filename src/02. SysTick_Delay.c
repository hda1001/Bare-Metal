/*
 * SysTick_Delay.c
 *
 *  Created on: 10-Dec-2019
 *      Author: black_Pearl
 */


#include "stm32f4xx.h"
void systickDelay(int n);

int main(void){
//	DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STOP | DBGMCU_STANDBY, ENABLE);
	RCC->AHB1ENR =1;
	GPIOA->MODER |= (1<<10);

	while(1){
//		DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STOP | DBGMCU_STANDBY, ENABLE);
		systickDelay(1000);
		GPIOA->ODR ^= (1<<5);
	}
}

void systickDelay(int n){
//	DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STOP | DBGMCU_STANDBY, ENABLE);

	for(int i=0; i< n; i++){
	SysTick->LOAD = 16000; 	// 10msec = val x 62.5 n
		SysTick->VAL = 0;		// current value is 0
		SysTick->CTRL = 0x5;
		// wait till count flag is set
		while((SysTick->CTRL & (1<<16))==0);
	}
//	SysTick->CTRL = 0;		// Timer Disable
}



