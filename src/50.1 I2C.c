/*
 * 50.1 I2C.c
 *
 *  Created on: 02-Jan-2020
 *      Author: black_Pearl
 */

#include<stm32f4xx.h>
#include<string.h>
#include<stdio.h>
void gpio_init();
void i2c_button_init();
void i2c_init();
void delay(int n){
	for(int i=0; i<1000*n; i++);
}
uint8_t data[] = "We are testing I2C\n";

int main(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	gpio_init();
	i2c_button_init();
	i2c_init();
	I2C_GenerateSTART(I2C1, ENABLE);
	while(1){
		GPIOA->ODR ^= (1<<5);
		I2C_Send7bitAddress(I2C1, 0x68, I2C_Direction_Transmitter);
		I2C_SendData(I2C1, data);

		delay(1000);
	}
}

void i2c_init(){
	I2C_InitTypeDef i2c;
	i2c.I2C_Ack = I2C_Ack_Enable;
	i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2c.I2C_ClockSpeed = 100000;
	i2c.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c.I2C_Mode = I2C_Mode_I2C;
	i2c.I2C_OwnAddress1 = 0x61;
	I2C_Init(I2C1, &i2c);

}

void gpio_init(){
	GPIO_InitTypeDef	LED;
	LED.GPIO_Pin = GPIO_Pin_5;
	LED.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	LED.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOA, &LED);

	GPIO_InitTypeDef	Bttn;
	Bttn.GPIO_Mode = GPIO_Mode_IN;
	Bttn.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &Bttn);
}

void i2c_button_init(){
	GPIO_InitTypeDef	ic;
	ic.GPIO_Mode = GPIO_Mode_AF;
	ic.GPIO_OType = GPIO_OType_OD;
	ic.GPIO_PuPd = GPIO_PuPd_UP;
	ic.GPIO_Speed = GPIO_Fast_Speed;
	ic.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB, &ic);

	ic.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &ic);

	GPIO_PinAFConfig(GPIOB, GPIO_Pin_6, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_Pin_9, GPIO_AF_I2C1);
}


