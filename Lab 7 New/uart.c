//#include "stm32f4xx.h" 
#include "uart.h"


void UART3Config (void){
		
	// 1. Enable the UART1 CLOCK and GPIO CLOCK
	RCC->APB1ENR |= (1<<18);  // Enable UART3 CLOCK
	RCC->AHB1ENR |= (1<<3); // Enable GPIOD CLOCK
	
	// 2. Configure the UART PINs for ALternate Functions
	GPIOD->MODER |= (1<<17);  // Bits (21:20)= 1:0 --> Alternate Function for Pin PD8
	GPIOD->MODER |= (1<<19);  // Bits (19:18)= 1:0 --> Alternate Function for Pin PD9
	
	GPIOD->AFR[1] |= (7<<4);  //   AF7 Alternate function for USART3 at Pin PD9
	GPIOD->AFR[1] |= (7<<0); //    AF7 Alternate function for USART3 at Pin PD8
	
	// 3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	USART3->CR1 = 0x00;  // clear all
	USART3->CR1 |= (1<<13);  // UE = 1... Enable USART
	
	// 4. Program the M bit in USART_CR1 to define the word length.
	USART3->CR1 &= ~(1<<12);  // M =0; 8 bit word length
	USART3->CR2 =0x00;
	// 5. Select the desired baud rate using the USART_BRR register.
	
	//USART3->CR3 &= ~USART_CR1_OVER8;
	
	USART3->BRR	 =0x0683; //@16Mhz

	// 6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register
	USART3->CR1 |= (1<<2); // RE=1.. Enable the Receiver
	USART3->CR1 |= (1<<3);  // TE=1.. Enable Transmitter
}


void UART3_SendChar (uint8_t c){
	
	USART3->DR = c; // load the data into DR register
	while (!(USART3->SR & (1<<7)));  // Wait for TC to SET.. This indicates that the data has been transmitted
	//USART3->DR = c;
}
	

void UART3_SendString (char *string){
	while (*string) UART3_SendChar (*string++);
}

uint8_t UART3_GetChar (void){
	uint8_t temp;
	
	while (!(USART3->SR & (1<<5)));  // wait for RXNE bit to set
	temp = USART3->DR;  // Read the data. This clears the RXNE also
	return temp;
}
	

