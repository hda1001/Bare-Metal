/*
 * 06. Systick_Timer_Interrupt.c
 *
 *  Created on: 14-Dec-2019
 *      Author: black_Pearl
 */
/*
 * Configure Systick interrupt to toggle LED
 * at 1Hz, System clock is 45MHz.
 */
#include<stm32f4xx.h>

int main(){
	//SystemCoreClock = 16000000;
//	__disable_irq();
	RCC->AHB1ENR |= 0x1;
	GPIOA->MODER |= 0x400;

	SysTick->LOAD = 0xFFFFFF-1;
	SysTick->VAL =0;
	SysTick->CTRL = 0x7;		// considering SysInt also

	NVIC_EnableIRQ(SysTick_IRQn);
//	__enable_irq();
	while(1);

	return 0;
}

void SysTick_Handler(void){
	GPIOA->ODR ^= (1<<5);

}
