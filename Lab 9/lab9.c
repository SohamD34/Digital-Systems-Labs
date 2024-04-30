#include <stm32f412zx.h>

void delay(int dd){
	for(int i=0;i<dd;++i){
		for(int j=0;j<dd;++j){
		}
	}
}

int main(){
	
	RCC->AHB1ENR |= 1; 			// enable clock
	
	GPIOA->MODER = 0x555555555;  // configuring 7 segments i.e. 7 GPIOA registers to output mode 01 => 01/0101/0101/0101/0000
	GPIOA->ODR = 0xFFF;			 // ODR = 1 1 1 1 / 1 1 1 1 / 1 1 1 0
	//																PA8 PA7	PA6 PA5 PA4 PA3 PA2	PA1	PA0
											
	// 0 -- ABCDEF -- PA1, PA2, PA3, PA4, PA5, PA6 --> 0 0111 1110 --> 0x07E
	// 1 -- B,C = 1 --> PA2, PA3 --> 0/0000/1100 --> 0X0C
	// 2 -- ABGED --> PA1, PA2, PA4, PA5, PA7 --> 0 1011 0110 --> 0x0B6
	// 3 -- ABGCD --> PA1, PA2, PA3, PA4, PA7 --> 0 1001 1110 --> 0x09E
	// 4 -- FGBC --> PA2 PA3, PA6, PA7 --> 0 1100 1100 -> 0x0CC
	// 5 -- AFGCD --> PA1 PA3 PA4 PA6 PA7 --> 0 1101 1010 --> 0X0DA
	// 6 -- AFGECD --> PA1 PA3 PA4 PA5 PA6 PA7 --> 0 1111 1010 --> 0x0FA
	// 7 -- ABC --> PA1 PA2 PA3 --> 0 0000 1110 -> 0X00E
	// 8 -- ABCDEFG --> 
	// 9 -- ABCDFG --> 0 1101 1110 --> oxoDE
	
	while(1){
		GPIOA->ODR = 0x07E;
		delay(1000);
		
		GPIOA->ODR = 0x00C;
		delay(1000);
		
		GPIOA->ODR = 0x0B6;
		delay(1000);
		
		GPIOA->ODR = 0x09E;
		delay(1000);
		
		GPIOA->ODR = 0x0CC;
		delay(1000);
		
		GPIOA->ODR = 0x0DA;
		delay(1000);
		
		GPIOA->ODR = 0x0FA;
		delay(1000);
		
		GPIOA->ODR = 0x00E;
		delay(1000);
		
		GPIOA->ODR = 0XFFF;
		delay(1000);
		
		GPIOA->ODR = 0x0DE;
		delay(1000);
	}
	
	return 0;
}