/*
 * 50. I2C_RTC.c
 *
 *  Created on: 01-Jan-2020
 *      Author: black_Pearl
 */

/*
PB8 -- SCL
PB9 -- SDA
*/

#define SLAVE_ADDR	0x68

#include "stm32f4xx.h"                  // Device header
void i2c_init(void);
int i2c_read_byte(char slv_addr,char memry_addr, char *data);
void delay(int n);
int main(){
	char data;
	i2c_init();
	RCC->AHB1ENR |= 1;
	GPIOA->MODER =0x400;


	while(1){
		i2c_read_byte(SLAVE_ADDR, 0, &data);
		if(data & 1){
			GPIOA->ODR = 0x20;
		}else{
			GPIOA->ODR = 0;
		}
		delay(10);
	}
}

void i2c_init(void){
	RCC->AHB1ENR |= 2;		//GPIOB
	RCC->APB1ENR |= 0x200000;

	GPIOB->MODER = 0xA0000; 	//PB8, PB9 as ALT Fn
	GPIOB->AFR[1] = 0x44;			// AF4 to PB8 and PB9

	GPIOB->OTYPER = 0x300;	//set as open-drain
	GPIOB->PUPDR = 0x50000;	// pull ups

	//I2C configuration
	I2C1->CR1 = 0x8000;		// Software Reset
	I2C1->CR1 &= ~0x8000;	// Disable the reset

	I2C1->CR2 = 0x10;			// 100 KHz Standard Mode	// Didnt understood
	I2C1->CCR = 80;				// 100KHz
//	I2C1->TRISE = 17;			// Max Rise Time			// Didnt understood
	I2C1->CR1  = 0x1;			// EN I2C

}

int i2c_read_byte(char slv_addr,char memry_addr, char *data){
	volatile int temp;

	while(I2C1->SR2 & 0x2);		// Busy Flag



				// send the slave address and wait until it is set

		/* **************************Start Condition ***********************************************
		 * Event 5: SB=1, cleared by reading SR1 register followed by writing DR register with address
		 ********************************************************************************************/
	I2C1->CR1	|= 0x100;		// Start Condition	---- Event 5 execute
	while(!(I2C1->SR1 & 0x1));	// wait until start bit is set/generated
	I2C1->DR = slv_addr<<1;		// Write the slave address

		/* ***************************************************************************
		 * Event 6: ADDR =1,cleared by reading SR1 register followed by reading SR2
		 ******************************************************************************/

	while(!(I2C1->SR1 &0x2));		// wait until address is matched
	temp = I2C1->SR2;				// SR2 will be cleared by reading the data	--- Event 6 execute
	while(!(I2C1->SR1 & 0x80));		// TXE = 1:	wait until data register gets empty

		/* ******************************************************************************
		 * Event 8_1: Shift register empty, Data register empty, write data in DR register
		 ********************************************************************************/

	I2C1->DR = memry_addr;			// send the memory address --- 0 for Write	--- Event 8_1 execution
	while(!(I2C1->SR1 & 0x80));		// TXE=1: wait until data register gets empty

	I2C1->CR1 |= 0x100;					// generate repeated start condition
	while(!(I2C1->SR1 & 0x1));	// wait until start bit is set/generated

	// 3. Now we need to read the data from I2C
	I2C1->DR = slv_addr<< 1|1;	// Read the data R/W = 1
	while(!(I2C1->SR1 &0x2));		// wait until address is matched
	I2C1->CR1 &= ~0x400;				// stop bit
	temp = I2C1->SR2;

	I2C1->CR1 |= 0x200;				// stop bit is generated
	while(!(I2C1->SR1 &0x40));		// wait until data register gets empty
	*data++ = I2C1->DR;
	return 0;
}

void delay(int n){
	for(int i=0; i>3195*n; i++);
}
