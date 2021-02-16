/*
 * BH1745.c
 *
 *  Created on: Feb 16, 2021
 *      Author: VIGNESH
 */

#include "main.h"
#include "BH1745.h"
#include "stdio.h"

//Function Prototype 1. Reset BH1745


int Reset_BH1745(void)

{
	int state;

	uint8_t tx_buffer = 0x8B;

	uint8_t rx_buffer[2] = {0,0};

	state = HAL_I2C_Mem_Write(&hi2c1, BH1745_ADDR, SYS_CNTRL_ADDR, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, HAL_MAX_DELAY);

	if(state != HAL_OK)
	{
		return 0;
	}

	HAL_I2C_Mem_Read(&hi2c1, BH1745_ADDR, SYS_CNTRL_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 1, 100);

	if(rx_buffer[0] == 0x0B)
	{
		return OK;
	}


	return 0;
}

//Function Prototype 2. Initializing BH1745

int Initialize_BH1745(void){


	int state;

	uint8_t rx_buff[2] = {0,0};

	state = HAL_I2C_Mem_Read(&hi2c1, BH1745_ADDR, MANUFAC_ID_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buff, 1, HAL_MAX_DELAY);

	if(state != HAL_OK)
	{
		return 0;
	}

	if(rx_buff[0] == 0xE0)
	{
		return OK;
	}


	return 0;
}


//Function Prototype 3. Setting measurement Time to 640 milliseconds

int set_measurement_time(void)
{

	int state;

	uint8_t tx_buffer = 0x02;

	uint8_t rx_buffer[2] = {0,0};

	state = HAL_I2C_Mem_Write(&hi2c1, BH1745_ADDR, MODE_CONTROL1_ADDR, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, HAL_MAX_DELAY);

	if(state != HAL_OK)
	{
		return 0;
	}

	HAL_I2C_Mem_Read(&hi2c1, BH1745_ADDR, MODE_CONTROL1_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 1, 100);

	if(rx_buffer[0] == 0x02)
	{
		return OK;
	}

	return 0;

}

//Function Prototype 4: Activate BH1745 for Measurement


int activate_measument(void)
{
	int state;

	uint8_t tx_buffer = 0x10;

	uint8_t rx_buffer[2] = {0,0};

	state = HAL_I2C_Mem_Write(&hi2c1, BH1745_ADDR, MODE_CONTROL2_ADDR, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, HAL_MAX_DELAY);

	if(state != HAL_OK)
	{
		return 0;
	}

	HAL_I2C_Mem_Read(&hi2c1, BH1745_ADDR, MODE_CONTROL2_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 1, 100);

	if((rx_buffer[0] == 0x10) || (rx_buffer[0] == 0x90))
	{
		return OK;
	}

	return 0;

}


//Function Prototype 5: Read RED


uint16_t Read_RedData(void)
{
	int state;

	uint8_t rx_buffer[2] = {0,0};

	uint16_t reg;

	state = HAL_I2C_Mem_Read(&hi2c1, BH1745_ADDR, RED_DATA_LSB_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 1, 640);

	if(state != HAL_OK)
	{
		return 0;
	}

	reg = ((rx_buffer[1] << 8) | (rx_buffer[0]));

	return reg;

}

//Function Prototype 6: Read Green

uint16_t Read_GreenData(void)
{
	int state;

	uint8_t rx_buffer[2] = {0,0};

	uint16_t reg;

	state = HAL_I2C_Mem_Read(&hi2c1, BH1745_ADDR, GREEN_DATA_LSB_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 1, 640);

	if(state != HAL_OK)
	{
		return 0;
	}

	reg = ((rx_buffer[1] << 8) | (rx_buffer[0]));

	return reg;

}

//Function Prototype 7: Read Blue


uint16_t Read_BlueData(void)
{
	int state;

	uint8_t rx_buffer[2] = {0,0};

	uint16_t reg;

	state = HAL_I2C_Mem_Read(&hi2c1, BH1745_ADDR, BLUE_DATA_LSB_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 1, 640);

	if(state != HAL_OK)
	{
		return 0;
	}

	reg = ((rx_buffer[1] << 8) | (rx_buffer[0]));

	return reg;

}
