#include "stm32f4xx.h"
#include "uart.h"
#include <stdio.h>
#define ARM_MATH_CM4

void GPIO_Init(void);
void TIM2_us_Delay(uint32_t delay); //TIM2 for generating 10us pulse for trig pin

void GPIO_Init(){
	
		//Configuring PA5 for generating pulse sent to trig pin
		RCC->AHB1ENR |= 1; //Enable GPIOA clock
		GPIOA->MODER |= 1<<10; //Set the PA5 pin to output mode

		//Configuring output from echo pin to be sent to the board (PA6 pin)
		GPIOA->MODER &= ~(0x00003000); //Set PA6 to input mode
		GPIOA->ODR = 0x00000000; // Setting trig pin to low to initialize the module
}

void TIM2_us_Delay(uint32_t delay){

}

int main(){

		UART3Config();
		UART3_SendString ("hello world12345\r\n");
		GPIO_Init();
	
		int time_diff;
		int pulsewidth;
		int toggle = 0;
		int val1;					// store initial value of count register
		int val2;					// store final value of count register

		while(1){
				
				GPIOA->ODR |= 1<<7;							// keep output pin high --> sound emitted
				RCC->APB1ENR |=1; 							//Start the clock for the timer peripheral

				// delay = 10 us --> f = 1/(10^-5) = 10^5 Hz = 0.1MHz	 freq = 16 MHz	PSC = 0 --> PSC+1 = 1
				// 0.1 = 16/(ARR+1) --> ARR = 159, PSC = 0

				TIM2->ARR = 159;
				TIM2->PSC = 0;
				TIM2->CNT = 0;
				TIM2->CR1 |= 1; 											//Start the Timer
				while(!(TIM2->SR & TIM_SR_UIF)){			//Polling the update interrupt flag
						if(!(TIM2->CNT &  TIM2->ARR)){
								TIM2->CNT += 1;
						}
				} 
				TIM2->SR &= ~(0x0001); 								//Reset the update interrupt flag
			
				if((GPIOA->IDR == 1<<6) && (toggle==0)){
						toggle = 1;
						val1 = TIM2->CNT;
				}
				if((GPIOA->IDR == 0) && (toggle==1)){
						toggle = 0;
						val2 = TIM2->CNT;
				}
				time_diff = val2 - val1;
				pulsewidth = time_diff/58;
				printf("%d\n",pulsewidth); 
				// fprintf("%d\n",pulsewidth);
		}
}