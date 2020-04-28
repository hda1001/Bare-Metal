/*
 * LCD.c
 *
 *  Created on: 06-Dec-2019
 *      Author: black_Pearl
 */


/*
 *	PC0 -PC7	D0-D7
 *	PB5			RS
 *	PB6			RW
 *	PB7			EN
 */

#include "stm32f4xx.h"

/*


void LCD_Data(char data){
	GPIOB->BSRR =  RS;							//	5 bit is set	RS=1
	GPIOB->BSRR = RW<<16; 					//	6 bit is reset RW=0
//	GPIO_WriteBit(GPIOB, GPIO_Pin_5, 1);		// Data Instruction
//	GPIO_WriteBit(GPIOB, GPIO_Pin_6, 0);		// Write Data
//	GPIOC->ODR &= ~(0xFF);						// Clearing ODR
	GPIOC->ODR = data;
	GPIOB->BSRR = EN;	//
//	GPIO_WriteBit(GPIOB, GPIO_Pin_7, 1);	// ????
	delay(0);
	GPIOB->BSRR = EN<<16;
//	GPIO_WriteBit(GPIOB, GPIO_Pin_7, 0);		// Send Data
}

void delay(int a){
	for(int i=0; i< 3276*a; i++);
}

 */

#define RS	0x20		//0010 0000 	bit 5
#define RW	0x40		//	0100 0000 	bit 6
#define EN	0x80		// 1000 0000	bit 7

void GPIO_Initi(void);
void LCD_Command(unsigned char command);
void delay(int a);
void LCD_Data(char data);
void LCD_Init(void);

int main(void){
	LCD_Init();
		while(1){
			delay(1);
			LCD_Data('X');
			delay(1);
			LCD_Data('H');
			delay(1);
			LCD_Data('E');
			delay(1);
			LCD_Data('L');
			delay(1);
			LCD_Data('L');
			delay(1);
			LCD_Data('O');
			delay(50);

			LCD_Command(1);		// Clear Screen
		}
}

void LCD_Init(void){
	GPIO_Initi();

	// Init Sequence
	delay(30);
	LCD_Command(0x30);
	delay(10);
	LCD_Command(0x30);
	delay(1);
	LCD_Command(0x30);

	LCD_Command(0x38);				// Set 8 bit data mode, 2 line, 5x7 font size
	LCD_Command(0x06);				// move cursor right
	LCD_Command(0x01);				// clear screen, move cursor home
	LCD_Command(0x0F);				// turn display, blink cursor
}

void GPIO_Initi(void){
	// Clock Initialization
		RCC->AHB1ENR |= 0x06;		// PB and PC Enable

		// Pin Configuration
		GPIOB->MODER |= 0x5400;
//		GPIOB->BSRRL |= 0x00C0;			// Set EN and RW LOW
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, 0);
		GPIO_WriteBit(GPIOB, GPIO_Pin_7, 0);

		// Set PC0 to PC7 as Data Output pins
		GPIOC->MODER |= 0x00005555;

}

void LCD_Command(unsigned char command){


//		GPIOB->BSRRH = (RS| RW);
	//	GPIOB->BSRR = (RS| RW);				//	RS=0, RW=0
		GPIO_WriteBit(GPIOB, GPIO_Pin_5, 0);	// Command Instruction
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, 0);	// Write Instruction

		GPIOC->ODR &= ~(0xFF);					// Clearing ODR
		GPIOC->ODR |= command;	//
//		GPIOB->BSRRL = EN;	//					// 7 bit is set		EN Set
		GPIO_WriteBit(GPIOB, GPIO_Pin_7, 1);	// Execute Instruction
		delay(1);
//		GPIOB->BSRRH = EN ;	//					// 7 bit is reset	EN=clear
		GPIO_WriteBit(GPIOB, GPIO_Pin_7, 0);	// Send Data
}

void LCD_Data(char data){
//		GPIOB->BSRRL =  RS;							//	5 bit is set	RS=1
//		GPIOB->BSRRH = RW; 					//	6 bit is reset RW=0
		GPIO_WriteBit(GPIOB, GPIO_Pin_5, 1);		// Data Instruction
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, 0);		// Write Data
	//	GPIOC->ODR &= ~(0xFF);						// Clearing ODR
		GPIOC->ODR = data;
//		GPIOB->BSRRL = EN;	//
		GPIO_WriteBit(GPIOB, GPIO_Pin_7, 1);	// ????
		delay(0);
//		GPIOB->BSRRH = EN;
		GPIO_WriteBit(GPIOB, GPIO_Pin_7, 0);		// Send Data


}

void delay(int a){
	for(int i=0; i< 3276*a; i++);
}
