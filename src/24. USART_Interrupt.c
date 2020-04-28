/*
 * 12. USART_Interrupt.c
 *
 *  Created on: 14-Dec-2019
 *      Author: black_Pearl
 */

#include<stm32f4xx.h>

void USART2_Init(void);
void systickDelay(int n);
void led_blink(char ch);

int main(){
	RCC->AHB1ENR = 0x1;
	GPIOA->MODER = 0x400;
	USART2_Init();
	USART2->CR1 |= 0x0020;		// RXNE Interrupt
	NVIC_EnableIRQ(USART2_IRQn);

	while(1);
	return 0;
}

void USART2_Init(void){
	RCC->APB1ENR |= 0x20000;	//(1<<17);		// USART2 ENABLE
	RCC->AHB1ENR |= 1;				//(1<<0);			// GPIOA Enable
	GPIOA->AFR[0] |= 0x7000;	// PA3 AF7
	GPIOA->MODER |= 0x0080;		// PA3 Set
	USART2->BRR = 0x008B;			// 115200 @ 16 MHz
	USART2->CR1 |= 0x4;			// RE Enable
	USART2->CR1 |= 0x2000;		// UE Enable_WordLength_8b;
}

void led_blink(char ch){
	if(ch%16 != 0){
		//GPIOA->ODR ^= (1 << 5);
		GPIOA->BSRRL = 0x20;			// 5 bit		// 0x20
		systickDelay(1000);
		GPIOA->BSRRH = ((0x20));				//0x002
		systickDelay(1000);
	}
	systickDelay(1000);
}

void systickDelay(int n){
//	DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STOP | DBGMCU_STANDBY, ENABLE);

	for(int i=0; i< n; i++){
	SysTick->LOAD = 16000-1; 	// 10msec = val x 62.5 n
		SysTick->VAL = 0;		// current value is 0
		SysTick->CTRL = 0x5;
		// wait till count flag is set
		while((SysTick->CTRL & (1<<16))==0);
	}
	SysTick->CTRL = 0;		// Timer Disable
}

void USART2_IRQHandler(void){
	char c;
	if(USART2->SR &(0x20)){
		c = USART2->DR;
		led_blink(c);
	}
}


