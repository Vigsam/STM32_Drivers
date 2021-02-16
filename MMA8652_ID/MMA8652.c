/*
 * MMA8652.c
 *
 *  Created on: Feb 15, 2021
 *      Author: VIGNESH
 */


#include "main.h"
#include "MMA8652.h"
#include "stdio.h"

I2C_HandleTypeDef hi2c1;


int Is_MMA8652_Detected(void)
{
	int state;

	uint8_t rx_buffer_detection[2] = {0,0};

	state = HAL_I2C_Mem_Read(&hi2c1, MMA8652_ADDR, 0x0D, I2C_MEMADD_SIZE_8BIT, rx_buffer_detection, 1, 100);

	if(state != HAL_OK)
	{
		return 0;
	}

	if(rx_buffer_detection[0] == 0x4A)
	{

		return 1;
	}

	return 0;

}

int MMA8652_Initialize(void)
{
	uint8_t tx_buffer;

	int state;


	//1. Enable the Self test Run for MMA8652 in Control Register 2

    tx_buffer = 0x40;

    state = HAL_I2C_Mem_Write(&hi2c1, MMA8652_ADDR, CONTROL_REG_2_ADDR, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, 100);

	if(state != HAL_OK)
	{
		return SELF_TEST_ERROR;
	}


	HAL_Delay(500);


	//2. Clearing all the bits in Control Register 1

	tx_buffer = 0x00;

	state = HAL_I2C_Mem_Write(&hi2c1, MMA8652_ADDR, CONTROL_REG_1_ADDR, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, 100);

	if(state != HAL_OK)
	{
		return 0;
	}

	HAL_Delay(200);

	//3. Data rate selection for 1.56 Hz in control Register 1 and Set to active


	tx_buffer = 0x35;

	state = HAL_I2C_Mem_Write(&hi2c1, MMA8652_ADDR, CONTROL_REG_1_ADDR, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, 100);

	if(state != HAL_OK)
	{
		return DATA_RATE_SELECTION_ERROR;
	}

	HAL_Delay(200);

	return OK;

}

uint16_t GET_X_Axis(void)
{
	uint16_t reg;
	uint8_t rx_buffer[2] = {0,0};
	int state;

	state = HAL_I2C_Mem_Read(&hi2c1, MMA8652_ADDR, DATA_X_AXIS_MSB_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 2, 100);

	if(state != HAL_OK)
	{
		return DATA_READ_ERROR;
	}

	reg = rx_buffer[0];

	reg = (reg << 4) | (rx_buffer[1] >> 4);

	return reg;
}

uint16_t GET_Y_Axis(void)
{
	uint16_t reg;

	uint8_t rx_buffer[2] = {0,0};

	int state;

	state = HAL_I2C_Mem_Read(&hi2c1, MMA8652_ADDR, DATA_Y_AXIS_MSB_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 2, 100);

	if(state != HAL_OK)
	{
		return DATA_READ_ERROR;
	}

	reg = rx_buffer[0];

	reg = (reg << 4) | (rx_buffer[1] >> 4);

	return reg;



}

uint16_t GET_Z_Axis(void)
{

	uint16_t reg;

	uint8_t rx_buffer[2] = {0,0};

	int state;

	state = HAL_I2C_Mem_Read(&hi2c1, MMA8652_ADDR, DATA_Y_AXIS_MSB_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 2, 100);

	if(state != HAL_OK)
	{
		return DATA_READ_ERROR;
	}

	reg = rx_buffer[0];

	reg = (reg << 4) | (rx_buffer[1] >> 4);

	return reg;


}
