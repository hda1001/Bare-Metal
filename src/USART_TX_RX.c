/*
 * USART_TX_RX.c
 *
 *  Created on: 10-Dec-2019
 *      Author: black_Pearl
 */

#include<stm32f4xx.h>
#include<string.h>
#include<stdio.h>
void RCC_Configuration(void)
{
/* --------------------------- System Clocks Configuration -----------------*/
/* USARTA clock enable */
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
/* GPIOA clock enable */
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
}

void GPIO_Configuration(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
/*-------------------------- GPIO Configuration ----------------------------*/
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; // PA.2 USART2_TX, PA.3 USART2_RX
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_Init(GPIOA, &GPIO_InitStructure);
/* Connect USART pins to AF */
GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
}

void USART2_Configuration(void)
{
USART_InitTypeDef USART_InitStructure;
/* USARTx configuration ------------------------------------------------------*/
/* USARTx configured as follow:
- BaudRate = 115200 baud
- Word Length = 8 Bits
- One Stop Bit
- No parity
- Hardware flow control disabled (RTS and CTS signals)
- Receive and transmit enabled
*/
USART_InitStructure.USART_BaudRate = 115200;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1;
USART_InitStructure.USART_Parity = USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
USART_Init(USART2, &USART_InitStructure);
USART_Cmd(USART2, ENABLE);
}

int main(void)
{
	FILE *ptr;
	ptr = fopen("test.txt","w");
	RCC_Configuration();
	GPIO_Configuration();
	USART2_Configuration();
	char str[50];
	char *s = str;
	while(1) // Don't want to exit
		{
		uint16_t Data;
		while(!(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)); // Wait for Char
		Data = USART_ReceiveData(USART2); // Collect Char
		str[50] = USART_ReceiveData(USART2);
		for(int i=0; str[i] !='\0'; i++){
			fprintf("%c", *s);
			s++;
//		}
		while(!(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == SET)); // Wait for Empty
		USART_SendData(USART2, Data); // Echo Char
		}
	}
}
