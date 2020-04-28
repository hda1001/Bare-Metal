/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
/*
 *	D7 -----	PA0  -----	PC7
 *	D6 -----	PA1  -----	PC6
 *	D5 -----	PA4  -----	PC5
 *	D4 -----	PB0  -----	PC4
 *	D3 -----	PC0  -----	PC3
 *	D2 -----	PC1  -----	PC2
 *	D1 -----	PC2  -----	PC1
 *	D0 -----	PC3  -----	PC0
 *
 *	RS	-----	PC13 ------ PB5
 *	R/W -----	PC14  ----- PB6
 *	E 	-----	Pc15  ----- PB7
 */
#include "stm32f4xx.h"

#define PIND0	GPIO_Pin_3
#define PIND1	GPIO_Pin_2
#define PIND2	GPIO_Pin_10
#define PIND3	GPIO_Pin_3
#define PIND4	GPIO_Pin_5
#define PIND5	GPIO_Pin_4
#define PIND6	GPIO_Pin_10
#define PIND7	GPIO_Pin_8
#define PORTA	GPIOA
#define PORTB	GPIOB

#define RS



void delay(int a);
void SendBit(GPIO_TypeDef *port, int pinNumber, uint8_t bitState);

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef LCD;
	LCD.GPIO_Mode = GPIO_Mode_OUT;
	LCD.GPIO_Speed = GPIO_Fast_Speed;
	LCD.GPIO_OType = GPIO_OType_PP;
	LCD.GPIO_PuPd = GPIO_PuPd_NOPULL;

	LCD.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(PORTA, &LCD);

	LCD.GPIO_Pin = PIND7;
	GPIO_Init(PORTA, &LCD);

	LCD.GPIO_Pin = PIND1;
	GPIO_Init(PORTA, &LCD);

	LCD.GPIO_Pin = PIND6;
	GPIO_Init(PORTA, &LCD);

	LCD.GPIO_Pin = PIND0;
	GPIO_Init(PORTB, &LCD);

	LCD.GPIO_Pin = PIND5;
	GPIO_Init(PORTB, &LCD);

	LCD.GPIO_Pin = PIND4;
	GPIO_Init(PORTB, &LCD);

	LCD.GPIO_Pin = PIND2;
	GPIO_Init(PORTB, &LCD);

	while(1){
		SendBit(PORTA, 8, 	0b10000000);
		SendBit(PORTB, 10, 	0b01000000);
		SendBit(PORTB, 4, 	0b00100000);
		SendBit(PORTB, 5, 	0b00010000);
		SendBit(PORTB, 3, 	0b00001000);
		SendBit(PORTA, 10, 	0b00000100);
		SendBit(PORTA, 2, 	0b00000010);
		SendBit(PORTA, 3, 	0b00000001);

		GPIOB->BSRRL |= GPIO_BSRR_BS_3;
		GPIOA->BSRRL |= GPIO_BSRR_BS_10;
		GPIOA->BSRRL |= GPIO_BSRR_BS_2;
		GPIOA->BSRRL |= GPIO_BSRR_BS_3;
	}
}

void delay(int a){
	for(int i=0; i<= 10000*a; i++);
}


void SendBit(GPIO_TypeDef *port, int pinNumber, uint8_t bitState){
	if(bitState & 0b00000001){
		port->BSRRL |= (1<<pinNumber);
	}else
		port->BSRRH |= (1<<pinNumber);
}
