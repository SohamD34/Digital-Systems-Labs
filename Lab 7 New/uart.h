#include "stm32f4xx.h" 
#include<stdio.h>
#include<string.h>
#include <stdint.h>

void UART3Config (void);
void UART3_SendChar (uint8_t c);
void UART3_SendString (char *string);
uint8_t UART3_GetChar (void);