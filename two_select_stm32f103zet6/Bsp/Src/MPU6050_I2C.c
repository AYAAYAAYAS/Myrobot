#include "main.h" 



void MPU6050_W_SCL(uint8_t BitValue)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, BitValue);
	Delay_us(10);
}

void  MPU6050_W_SDA(uint8_t BitValue)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, BitValue);
	Delay_us(10);
}


uint8_t MPU6050_R_SDA(void)
{
	uint8_t BitValue;
	BitValue =HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0);
	Delay_us(10);
	return BitValue;                                                                                                                                 
}


void  MPU6050_I2C_Start(void)
{
	MPU6050_W_SDA(1);
	MPU6050_W_SCL(1);
	MPU6050_W_SDA(0);
	MPU6050_W_SCL(0);
}

void MPU6050_Stop(void)
{
	MPU6050_W_SDA(0);
	MPU6050_W_SCL(1);
	MPU6050_W_SDA(1);
}

void MPU6050_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i ++)
	{
		MPU6050_W_SDA(Byte & (0x80 >> i));
		MPU6050_W_SCL(1);
		MPU6050_W_SCL(0);
	}
}

uint8_t MPU6050_ReceiveByte(void)
{
	uint8_t i, Byte = 0x00;
	MPU6050_W_SDA(1);
	for (i = 0; i < 8; i ++)
	{
		MPU6050_W_SCL(1);
		if (MPU6050_R_SDA() == 1){Byte |= (0x80 >> i);}
		MPU6050_W_SCL(0);
	}
	return Byte;
}

void MPU6050_SendAck(uint8_t AckBit)
{
	MPU6050_W_SDA(AckBit);
	MPU6050_W_SCL(1);
	MPU6050_W_SCL(0);
}

uint8_t MPU6050_ReceiveAck(void)
{
	uint8_t AckBit;
	MPU6050_W_SDA(1);
	MPU6050_W_SCL(1);
	AckBit = MPU6050_R_SDA();
	MPU6050_W_SCL(0);
	return AckBit;
}
