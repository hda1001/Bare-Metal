/*
 * 23. USART_TX_RX.c
 *
 *  Created on: 14-Dec-2019
 *      Author: black_Pearl
 */

// USART 2 APB1EN
// PA3 USART2 RX

// USART 2 APB1EN
// PA3 USART2 RX

#include "stm32f4xx.h"                  // Device header
#include <stdio.h>

int USART_write(int ch);
int USART_read(void);
void USART2_Init(void);
void delay(int var);
//void led_blink(char ch);
int fputc(int c, FILE *f);
char ch;
int data;

int main(void){
	/*
	RCC->AHB1ENR |= 1;		// GPIOA Enable
	GPIOA->MODER &= ~(3<<(2*5));		//GPIO MODE Settings
	GPIOA->MODER |= (1<<2*5);				// GPIO OUTPUT MODE
	GPIOA->OSPEEDR  &= ~(3 << (2*5));	// GPIO Pin Speed
	GPIOA->OSPEEDR  |= (3 << (2*5));	// FAST MODE
	GPIOA->OTYPER &= ~(1 << 5);			// GPIO OTYPE
	GPIOA->PUPDR &= ~(3 << (2*5));	// PUPD
	*/
	FILE *ptr;
	ptr =fopen("test.txt","a+");
	int n;
	char str[100];
	USART2_Init();


	printf("Hello from the other side\r\n");
	fprintf(stdout, "test for stdout \r \n");
	fprintf(stderr, "test for stderr \r\n");



	while(1){
		printf("How old are you?");
		scanf("%d", &n);
		printf("You age is: %d\r\n", n);
		printf("Enter your First name: ");
		gets(str);
		printf("I like your style: ");
		puts(str);
		printf("\r\n");
	}
}

void USART2_Init(void){
	RCC->APB1ENR |= 0x20000;	//(1<<17);		// USART2 ENABLE
	RCC->AHB1ENR |= 1;				//(1<<0);			// GPIOA Enable

	//GPIOA->AFR[0] |= 0x0700;	// PA3 AF7 TX
	GPIOA->AFR[0] |= 0x7700;	// PA3 AF7 RX
	GPIOA->MODER |= 0x00A0;		// PA2 and PA3 Set

	USART2->BRR = 0x0683;			// 115200 @ 16 MHz
	USART2->CR1 = 0x000C;			// TE and RE Enable
	USART2->CR1 |= 0x2000;		// UE Enable
}

int USART_write(int ch){
	while(!(USART2->SR & 0x0080));		// Wait till TXNE is 1
	USART2->DR = (ch & 0xFF);
	return ch;
}

int USART_read(void){
	// Check wthether DR is empty or not || TXE bit of SR ||
	while(!(USART2->SR & 0x0020));		// Wait till RXNE is 1
	data = USART2->DR;
	return (USART2->DR);
}

// Connect Embedded Code to the STDIO library for USART Communication
// printf, scanf, sprintf, fprintf all will work.
struct __FILE{int handle;};
	FILE __stdin   = {0};
	FILE __stdout  = {1};
	FILE __stderr  = {2};

	int fgetc(FILE *f){
		int c;
		c = USART_read();
		if(c == '\r'){
			USART_write(c);
			c = '\n';
		}
		USART_write(c);
		return c;
	}

int fputc(int c, FILE *f){
	return USART_write(c);
}


void delay(int var){
	for(int i=0; i< 3195*var; i++);
}

