#include "i2c.h"
#include "stm32f1xx.h"

static void delay (unsigned int time) {
    for (unsigned int i = 0; i < time; i++){
        for (volatile unsigned int j = 0; j < 2000; j++);
    }    
}

void i2c_init(){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOB->CRL |= GPIO_CRL_MODE6;
	GPIOB->CRL |= GPIO_CRL_CNF6;

	GPIOB->CRL |= GPIO_CRL_MODE7;
	GPIOB->CRL |= GPIO_CRL_CNF7;

	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;


	I2C1->CR2 &= ~(I2C_CR2_FREQ);
	I2C1->CR2 |= (8<<I2C_CR2_FREQ_Pos);

	I2C1->TRISE = 9;														// Rise time
	I2C1->CCR |= 0x28;
	I2C1->CR1 |= I2C_CR1_PE;
}

void i2c_start(void) {
    I2C1->CR1 |= (1 << 8);
    while(!(I2C1->SR1 & (1 << 0)));
}

void i2c_stop(void) {
    I2C1->CR1 |= (1 << 9);
    while(!(I2C1->SR2 & (1 << 1)));
}


uint8_t i2c_read2(uint16_t reg_address) 
{
    int8_t reg;
    int16_t r_msb, r_lsb;
    
    r_msb = (reg_address & 0xFF00) >> 8;
    r_lsb = reg_address & 0x00FF;
	
    i2c_start();
    I2C1->DR = device_address;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;																							  // Clear addr register

    I2C1->DR = r_msb;																								// Send operation type/register MSB
    while (!(I2C1->SR1 & I2C_SR1_BTF));

    I2C1->DR = r_lsb;																								// Send operation type/register LSB
    while (!(I2C1->SR1 & I2C_SR1_BTF));

    i2c_stop();																											// Restart by sending stop & start sig
    i2c_start();

    I2C1->DR = device_address | 0x01; 														  // read the device address
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    while (!(I2C1->SR1 & I2C_SR1_RXNE));
    reg = I2C1->DR;

    i2c_stop();

    return reg;
}

uint8_t i2c_read1(uint8_t reg_address) 
{
    uint8_t reg;
    i2c_start();
	
    I2C1->DR = DeviceAddr;													 // Send device address to establish connection
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    
    (void)I2C1->SR2; 																	// Dummy read to clear flags and SR reg
    
    I2C1->DR = reg_address;														//Sending operation type/register 
    while (!(I2C1->SR1 & I2C_SR1_BTF));

    i2c_stop();																				//Restarting transmission by sending stop & start sig
    i2c_start();

    I2C1->DR = DeviceAddr | 0x01; // read
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    
    while (!(I2C1->SR1 & I2C_SR1_RXNE));							//Wait until data arrived in receive buffer
    
    reg_val = (uint8_t)I2C1->DR;											//Read value
    i2c_stop();													    					//Send stop signal

    return reg_val;
}

void i2c_write_1byte(uint8_t regaddr, uint8_t data) {

    i2c_start();

    I2C1->DR = DeviceAddr;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));					 // Wait until transfer done
    (void)I2C1->SR2; 																// Clear address register

    I2C1->DR = reg_address;
    while (!(I2C1->SR1 & I2C_SR1_BTF)); 						// Wait until transfer done

    I2C1->DR = data;																// Sending data
    while (!(I2C1->SR1 & I2C_SR1_BTF));  						// Wait until transfer done

    i2c_stop();
}


void i2c_write_nbytes(uint8_t *data, uint8_t n) {
		
	int t1 = 0;
    i2c_start();

    I2C1->DR = device_address; 
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;														// clear flag using dummy read

    for(t1 = 0; t1 < n; t1++){
        I2C1->DR = data[t1];
        while (!(I2C1->SR1 & I2C_SR1_BTF));
    }    
    
    i2c_stop();
}




