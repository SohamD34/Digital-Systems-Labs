#include <stdio.h>
#include "stm32f412zx.h"

void delay(int dd);

int main(){
	RCC->AHB1ENR |= 0x02;
	GPIOB->MODER |= 0X10000000; 
	GPIOB->ODR = 0X4000;
	
	while(1){
		GPIOB->ODR = 0x4000;
		delay(400000);
		GPIOB->ODR = 0x00;
		delay(150000);
	}
}

void delay(int dd){
	int i;
	for (;dd>0; dd--){
	}
}
