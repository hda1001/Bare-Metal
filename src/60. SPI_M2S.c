/*
 * 60. SPI_M2S.c
 *
 *  Created on: 16-Apr-2020
 *      Author: black_Pearl
 */

/*
 * PB15 - SPI2_MOSI
 * PB14 - MISO
 * PB13 - SCLK
 * PB12 - NSS
 * ALT Function: 5
 */

#include<stm32f4xx.h>

int main(){
// *********************************************************** //
	RCC->AHB1ENR = 0x07;	// GPIOA, GPIOB, GPIOC
	RCC->APB1ENR = 0x24000;		// USART2 and SPI2

// *********************************************************** //
	GPIOA->MODER = 0x4A0;	// GPIOA 2,3,5
//	GPIOB->MODER = 0xAA000000;	// GPIOB 13, 14, 15
//	GPIOC->MODER = 0x0000;	// GPIOC 13
//
//	GPIOA->AFR[0] = 0x7700;
//	GPIOB->AFR[1] = 0x55550000;
//	/*
//	 * PB15 -> SPI2-> MOSI
//	 * PB14 -> SPI2->MISO
//	 * PB13 -> SCLK
//	 * PB12 -> NSS
//	 */
//
////	SYSCFG->EXTICR[4] = 0x20;
//	SPI2->CR1 = 0x315;
//	SPI2->CR1 = 0x4;
	GPIOA->ODR = 1<<5;
// *********************************************************** //

	while(1){
//	SPI2->CR1 |= (1<<6);	// SPE Enable

	}
	return 0;

}
