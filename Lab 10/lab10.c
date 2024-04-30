#include <stm32f412zx.h>
#include <stdio.h>

void delay(uint32_t delay){

    RCC->APB1ENR |=1; 										// Start the clock for the timer peripheral
		TIM2->PSC = 100;
    TIM2->ARR = (160000*delay)-1; 				// delay in microsecond 160000-1 = 159999
		TIM2->CNT = 0;
    TIM2->CR1 |= 1; 											//Start the Timer
    while(!(TIM2->SR & TIM_SR_UIF)){} 		//Polling the update interrupt flag
    TIM2->SR &= ~(0x0001); 								//Reset the update interrupt flag
}

void EXTI15_10_IRQHandler(void) {
	GPIOB->ODR = 0x00;
	delay(1);
	GPIOB->ODR = 0x80;
	delay(1);
	GPIOB->ODR = 0x0;
	delay(1);
	GPIOB->ODR = 0x80;
	delay(1);
	GPIOB->ODR = 0x0;
	delay(1);
	GPIOB->ODR = 0x80;
	EXTI->PR = 0x2000;
}

int main(){
	
	__disable_irq( );								
	
	// Interrupt Request Handler
	
	RCC->AHB1ENR |= 0x02 ; 						
	RCC->AHB1ENR |= 0x4 ; 						
	RCC->APB2ENR |= 0X4000 ; 				
	GPIOB->MODER |= 0x00004000 ; 			
	SYSCFG->EXTICR[3] = 0X0020 ; 			
	EXTI->IMR |= 0x2000 ; 						
	EXTI->RTSR |= 0x2000 ; 		
	
	
	// Once handling done, enable interrupt requests again
	
	NVIC_EnableIRQ (EXTI15_10_IRQn) ;				
	__enable_irq( ) ;	
	
	while(1) {	}
}

