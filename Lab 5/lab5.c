#include "stm32f412Zx.h"

int adcvalue; // Defining variable to watch ADC values


int main() {
	RCC->APB2ENR |= 0x100 ; // Enable clock for ADC1
	RCC->AHB1ENR |= 0x1 ; // Enable clock for GPIOA- PA0 is internally connected to IN 0 )
	ADC1->CR2 |= 0x2 ; // Enable continuous conversion mode
	ADC1->CR2 |= 0x400 ; // EOC after each conversion
	ADC1->CR2 |= 0x1 ; // ADON =1 enable ADC1
	ADC1->SQR3 |= 0 ; // Conversion in regular sequence
	GPIOA->MODER |= 0x3 ; // Analog mode for PA0
	GPIOB->MODER |= 0x4000;
	GPIOB->ODR=0x0;
	
	while ( 1 ) {
		
		ADC1->SR = 0 ; // Clear the status register
		ADC1->CR2 |= (0x40000000) ; // Starting conversion by SWSTART
		
		while (ADC1->SR & (0x2)) { // Check until conversion completes
			
			adcvalue = ADC1->DR; // Update ADC values to variable defined
			
			if ((double)adcvalue*3.3/4095 < 1.78) { // If voltage drops below 1.78V
				GPIOB->ODR = 0x80;
			} 
			else {
				GPIOB->ODR = 0x0; // Turn off LED
			}
		}
	}
}