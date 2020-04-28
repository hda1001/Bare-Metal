/*
 * 60. SPI_Master.c
 *
 *  Created on: 19-Apr-2020
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
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

void Send_data(uint8_t *data);
void delay();

void delay(){
	for(uint32_t i= 0; i<1000000; i++);
}

uint8_t buff[12]= "Hello World";
uint8_t str;

int main(){
// *********************************************************** //
	RCC->AHB1ENR = 0x07;	// GPIOA, GPIOB, GPIOC
	RCC->APB1ENR = 0x24000;		// USART2 and SPI2

// *********************************************************** //
	GPIOA->MODER |= 0x4A0;		// GPIOA 2,3,5
	GPIOB->MODER = 0xAA000000;	// GPIOB 13, 14, 15
	GPIOC->MODER = 0x0000;		// GPIOC 13

	GPIOA->AFR[0] = 0x7700;
	GPIOB->AFR[1] = 0x55550000;

//	SPI2->CR1 |= 0x315;			// SSM =1, and SSI = 1		NSS Software
	SPI2->CR1 |= 0x014;			// SSM =0, and SSI = 0		NSS Hardware
	SPI2->CR2 = 0x4;			// SSOE = 1 for toggling NSS

// *********************************************************** //

	while(1){
		if(((GPIOC->IDR >> 13) && 0x1) == 0){
			delay();
//			str = strlen(buff);
			SPI2->CR1 |= (1<<6);	// SPE Enable
//			Send_data((uint8_t*)12);
//			while(SPI2->SR & 0x80);
			Send_data(buff);
			while(SPI2->SR & 0x80);
			SPI2->CR1 &= ~(1<<6);	// SPE Disable
		}
	}

}

void Send_data(uint8_t *data){
	for(int i=0; i<13; i++){
		while(((SPI2->SR) & 0x80));
		SPI2->DR = (data[i] & 0xFF);
		while(((SPI2->SR) & 0x2) == 0);
	}
}
