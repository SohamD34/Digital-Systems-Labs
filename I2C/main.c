#include "stm32f412zx.h"
#include "i2c.h"
#include "uart.h"

static void delay (unsigned int time) {
    for (unsigned int i = 0; i < time; i++){
        for (volatile unsigned int j = 0; j < 2000; j++);
    }    
}

int main(void){

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;													// setup LEDs - GPIOD 12,13,14,15
    GPIOD->MODER &= ~(0xFFU << 24);
    GPIOD->MODER |= (0x55 << 24);
    GPIOD->ODR    = 0x0000;
    

    RCC->APB1ENR |= (1 << 21);
    RCC->AHB1ENR |= (1 << 1);																			// setup I2C - GPIOB 6 SCL, 9 SDA
    GPIOB->MODER &= ~(3 << (6 << 1)); 														//PB6 as SCK
    GPIOB->MODER |=  (2 << (6 << 1)); 
    GPIOB->OTYPER |= (1 << 6);        
    GPIOB->MODER &= ~(3 << (9 << 1)); 														//PB9 as SDA
    GPIOB->MODER |=  (2 << (9 << 1)); 
    GPIOB->OTYPER |= (1 << 9);        

    GPIOB->AFR[0] |= (4 << (6 << 2));    													// Alt function for PB6 SCK
    GPIOB->AFR[1] |= (4 << ((9-8) << 2)); 											  // Alt function for PB9 SDA

    I2C1->CR1 = I2C_CR1_SWRST;
    I2C1->CR1 = 0;

    
    I2C1->CR2 |= (10 << 0);   																		// Set I2C clock 10Mhz periph clock
    I2C1->CCR |= (50 << 0);
    I2C1->TRISE |= (11 << 0); 																		//Set TRISE to 11 eq. 100khz
    I2C1->CR1 |= I2C_CR1_PE; 																			//Enable i2c
    
    while(1){
        GPIOD->ODR |= (1 << 12); 
        delay(10);
        GPIOD->ODR &= ~(1 << 12); 
        delay(10);
    }
    return 0; 
}