#include "uart.h"
#include <stdio.h>
#include "stm32f412zx.h"

#define Perpher_CLK 8000000
#define Baudrate	115200

static uint16_t compute_uart_bd();
static void uart2_write();
static int __io_putchar();


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate){
	USARTx->BRR =  compute_uart_bd(PeriphClk,BaudRate);
}

void uart2_write(int ch){
	while(!(USART2->SR & USART_SR_TXE)){}										// Making sure the transmit data register is empty
	USART2->DR = (ch & 0xFF);															// Writing to transmit data register
}

int __io_putchar(int ch) {
	uart2_write(ch);
	return ch;
}


void uart2_init(){

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;												// Enable clock access to GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;										  	// Enable clock access to alternate function

	GPIOA->CRL |= GPIO_CRL_MODE2;															/*Confgiure PA2 as output maximum speed to 50MHz and alternate output push-pull mode*/
	GPIOA->CRL |= GPIO_CRL_CNF2_1;
	GPIOA->CRL &= ~GPIO_CRL_CNF2_0;

	AFIO->MAPR &= ~AFIO_MAPR_USART2_REMAP;


	RCC->APB1ENR|=RCC_APB1ENR_USART2EN;												// Enable clock access to USART2
	USART2->CR1 |= USART_CR1_TE;															// Transmitter Enable
	uart_set_baudrate(USART2,Perpher_CLK,Baudrate);						// Set baudrate using BRR
	USART2->CR1 |= USART_CR1_UE;															// Enable UART

}
