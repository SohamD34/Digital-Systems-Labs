#include <stm32f412zx.h>
#include <stdio.h>

// POTENTIOMETER EXPERIMENT - Use of ADC
// variable to temporarily store and read the adc readings

void delay(int dd){
	for(int i=0; i<dd; i++){
		for(int j=0; j<dd; j++){
		}
	}
}

int main(){
	//int adc_value; 										
	RCC->APB2ENR |= 0x100 ; // Enable clock for ADC1
	RCC->AHB1ENR |= 0x1 ; // Enable clock for GPIOA- PA0 is internally connected to IN 0 )
	RCC->AHB1ENR |=0x2;
	ADC1->CR2 |= 0x2 ; // Enable continuous conversion mode
	ADC1->CR2 |= 0x400 ; // EOC after each conversion
	ADC1->CR2 |= 0x1 ; // ADON =1 enable ADC1
	ADC1->SQR3 |= 0 ; // Conversion in regular sequence
	GPIOA->MODER |= 0x3 ; // Analog mode for PA0
	GPIOB->MODER |= 0x4000;
	GPIOB->ODR=0x0;
	int x = 0 ;
	while(1){
		x++;
		ADC1->SR = 0;									// Status register - cleared
		ADC1->CR2 |= 0x40000000;			// Control register -> 30th bit SWSTART = 1 --> Conversion takes place
		
		if (ADC1->SR & 0x02){
			float adc_value = ADC1->DR;				// store the value from Data Register to the variable.
			x=0;
			// Quantising the reading
			float reading = 0;
			reading = adc_value*3.3/4095;		// 12 bit register -> 4096
			
			if(reading < 1.78){
				GPIOB->ODR = 0x0080;			// Output reg for LED 7
				delay(100);
			}
		
			else{
				GPIOB->ODR = 0x0000;
			}
			
		}
	}
}