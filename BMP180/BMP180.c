/*
 * BMP180.c
 *
 *  Created on: Feb 17, 2021
 *      Author: VIGNESH
 */


#include "BMP180.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>


//Function Prototype 1. Initializing BMP180


//int16_t AC1,AC2,AC3,AC4,AC5,AC6,B1,B2,MB,MC,MD;

//int16_t UT,X1,X2,X3,B3,B4,B5,B6,B7;

short AC1 = 0;
short AC2 = 0;
short AC3 = 0;
unsigned short AC4 = 0;
unsigned short AC5 = 0;
unsigned short AC6 = 0;
short B1 = 0;
short B2 = 0;
short MB = 0;
short MC = 0;
short MD = 0;

long UT = 0;
short oss = 0;
long UP = 0;

long X1 = 0;
long X2 = 0;
long X3 = 0;

long B3 = 0;
unsigned long B4 = 0;
long B5 = 0;
long B6 = 0;
unsigned long B7 = 0;

float temp,Press,Alt;

int Initialize_BMP180()
{
	int state;

	uint8_t rx_buffer[2] = {0,0};

	state = HAL_I2C_Mem_Read(&hi2c2, BMP180_ADDR, BMP180_CHIP_ID_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 1, HAL_MAX_DELAY);

	if(state != HAL_OK)
	{
		return 0;
	}

	if(rx_buffer[0] == 0x55)
	{
		return OK;
	}

	return 0;
}

//Function prototype 2: Reset BMP180

int Reset_BMP180(void)
{
	int state;

	uint8_t tx_buffer = 0xB6;

	state = HAL_I2C_Mem_Write(&hi2c2, BMP180_ADDR, BMP180_RESET_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, HAL_MAX_DELAY);

	if(state != HAL_OK)
	{
		return 0;
	}

	return OK;
}


//Function Prototype 4:	Read_Calibration_Co_effiecients

int16_t Read_Calibration_Co_effiecients(void)
{
	int state;

	uint8_t rx_buffer[22] = {0};

	state = HAL_I2C_Mem_Read(&hi2c2, BMP180_ADDR, BMP180_COEFFIECIENT_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 22, 10);

	if(state != HAL_OK)
	{
		return 0;
	}

	AC1 = ((rx_buffer[0] << 8) | (rx_buffer[1]));
	AC2 = ((rx_buffer[2] << 8) | (rx_buffer[3]));
	AC3 = ((rx_buffer[4] << 8) | (rx_buffer[5]));
	AC4 = ((rx_buffer[6] << 8) | (rx_buffer[7]));
	AC5 = ((rx_buffer[8] << 8) | (rx_buffer[9]));
	AC6 = ((rx_buffer[10] << 8) | (rx_buffer[11]));
	B1 = ((rx_buffer[12] << 8) | (rx_buffer[13]));
	B2 = ((rx_buffer[14] << 8) | (rx_buffer[15]));
	MB = ((rx_buffer[16] << 8) | (rx_buffer[17]));
	MC = ((rx_buffer[18] << 8) | (rx_buffer[19]));
	MD = ((rx_buffer[20] << 8) | (rx_buffer[21]));

	return OK;

}


//Function prototype 5: Read Temperature Data

long Read_Uncompensated_Temperature_from_BMP180(void)
{
	int state;

	uint8_t tx_buffer = 0x2E;

	uint8_t rx_buffer[2] = {0,0};

	state = HAL_I2C_Mem_Write(&hi2c2, BMP180_ADDR, BMP180_CONTROL_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, 1000);

	HAL_Delay(5);

	HAL_I2C_Mem_Read(&hi2c2, BMP180_ADDR, BMP180_MSB_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 2, 1000);

	HAL_Delay(5);

	if(state != HAL_OK)
	{
		return 0;
	}

	UT =  ((rx_buffer[0] << 8) + (rx_buffer[1]));

	return UT;
}


//Function prototype 6: Calculate Temperature Value

float Read_Temperature_from_BMP180 (void)
{

	UT = Read_Uncompensated_Temperature_from_BMP180();
	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
	X2 = ((MC*(pow(2,11))) / (X1+MD));
	B5 = X1+X2;
	temp = (B5+8)/(pow(2,4));
	return temp/10.0;

}


//Function prototype 7: Read Un_compensated Pressure

long Read_Uncompensated_Pressure(int oss)
{

	int state;

	uint8_t tx_buffer = 0x34 + (oss<<6);

	uint8_t rx_buffer[3] = {0};

	state = HAL_I2C_Mem_Write(&hi2c2, BMP180_ADDR, BMP180_CONTROL_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, 1000);

	HAL_Delay(5);

	if(state != HAL_OK)
	{
		return 0;
	}

	state = HAL_I2C_Mem_Read(&hi2c2, BMP180_ADDR, BMP180_MSB_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 3, 1000);

	HAL_Delay(5);

	UP = ((rx_buffer[0] << 16) + (rx_buffer[1]<<8) + rx_buffer[2]) >> 8;

	return UP;

}


//Function prototype 8: Read Pressure

float Read_Pressure_from_BMP180(int oss)
{
	UP = Read_Uncompensated_Pressure(oss);
	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
	X2 = ((MC*(pow(2,11))) / (X1+MD));
	B5 = X1+X2;
	B6 = B5-4000;
	X1 = (B2 * (B6*B6/(pow(2,12))))/(pow(2,11));
	X2 = AC2*B6/(pow(2,11));
	X3 = X1+X2;
	B3 = (((AC1*4+X3)<<oss)+2)/4;
	X1 = AC3*B6/pow(2,13);
	X2 = (B1 * (B6*B6/(pow(2,12))))/(pow(2,16));
	X3 = ((X1+X2)+2)/pow(2,2);
	B4 = AC4*(unsigned long)(X3+32768)/(pow(2,15));
	B7 = ((unsigned long)UP-B3)*(50000>>oss);
	if (B7<0x80000000) Press = (B7*2)/B4;
	else Press = (B7/B4)*2;
	X1 = (Press/(pow(2,8)))*(Press/(pow(2,8)));
	X1 = (X1*3038)/(pow(2,16));
	X2 = (-7357*Press)/(pow(2,16));
	Press = Press + (X1+X2+3791)/(pow(2,4));

	Press = Press/100.0;

	return Press;
}

//Function prototype 8: Start BMP180 Sensor by Reading Coefficients

void BMP180_Start(void)
{
	Read_Calibration_Co_effiecients();

}


//Function Prototype 9: Measure Altitude

float Read_Altitude_from_BMP180(void)
{
	Read_Pressure_from_BMP180(0);
	/*Alt = 44330 * ((1) - (pow((Press/1013.25),(1/5.255))));
	return Alt;
	*/
	return 44330*(1-(pow(((float)Press/(float)1013.25), 0.19029495718)));

}
