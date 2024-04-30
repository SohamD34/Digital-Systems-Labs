#include "stm32f412Zx.h"
#include <stdio.h>

void delay(int dd);

int main() {
    RCC->AHB1ENR |= 0x02; 
    GPIOB->MODER |= 0x10004000; 
    GPIOB->ODR = 0x4000; 
		SysTick -> LOAD = 16000000;
		SysTick -> VAL = 0;
		SysTick -> CTRL = 0x5;
	
		int c = 0;
		
    while (1) {
				if (SysTick -> CTRL & 0x00010000){
						c++;
						if (c % 10 == 0){
							GPIOB -> ODR  ^= 0x4080;
						}
				}
		
		}

}