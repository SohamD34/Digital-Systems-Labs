#include <stm32f412zx.h>
#include <stdio.h>


int main(){

	RCC->AHB1ENR |= 0x10100; // Enable clock for GPIOC & GPIOE
	
	// Set to Output mode
	GPIOC->MODER |= 0x2;				// Output mode
	GPIOC->ODR |= 0x1;					// Set the output register to 1
	
	// Set timer using TIM2  --> 10us --> 10^5 Hz = 16 MHz/(0+1)(159+1) 
	// This timer will note the time at the start of process
	
	USART1->CR1 |= 0x4;
	USART1->CR2 |= 0x0;
	USART1->CR1 |= (1<<15);
	USART1->CR2 = 0x0;
	
	TIM2->ARR = 0;
	TIM2->PSC = 159;
	TIM2->CNT = 0;
	TIM2->CR1 |= 0x11;  		// start counting
	
	GPIOE->ODR = 0x010;			// turn Port E to Output to show LED 
	
	int t1;
	
	while(1){
		if(TIM2->SR & 1){
			TIM2->SR = 0;
			t1 = TIM2->CCR1;
			break;
		}	
	}
	
	// Set timer using TIM3  --> 10us --> 10^5 Hz = 16 MHz/(0+1)(159+1) 
	// This timer will note the time at the end of process
	
	int t2;
	
	RCC->APB1ENR = 0x01;
	TIM3->PSC = 1599;
	TIM3->ARR = 0;
	TIM3->CNT = 0;
	
	while(1){
		if (TIM3->SR & 1){
			TIM3->SR = 0;
			
			break;
	}
	
}