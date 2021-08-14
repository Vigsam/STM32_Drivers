/*
 * SI7021.c
 *
 *  Created on: August 14, 2021
 *      Author: VIGNESH
 */

#include "si7021.h"
#include <stdint.h>


uint8_t SI7021_Initialization()
{

	uint8_t rx_buffer[2] = {0,0};

	uint8_t state;

	state = HAL_I2C_Mem_Read(&hi2c1, SI7021_SLAVE_ADDR, SI7021_FIRMWARE_REVISION_ADDR, I2C_MEMADD_SIZE_16BIT, rx_buffer, 1, 1000);

	if(state != HAL_OK)
	{

		return 0;
	}

	if(rx_buffer[0] == 0x20 || rx_buffer[0] == 0xFF)
	{

		return SI7021_OK;
	}

	return 0;
}

uint8_t SI7021_Set_Resolution()
{

	uint8_t rx_buffer[2] = {0x3A,0};

	uint8_t state;

	state = HAL_I2C_Mem_Write(&hi2c1, SI7021_SLAVE_ADDR, SI7021_USER_WRITE_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &rx_buffer[0], 1, 1000);

	if(state != HAL_OK)
	{
		return 0;
	}

	state = HAL_I2C_Mem_Read(&hi2c1, SI7021_SLAVE_ADDR, SI7021_USER_READ_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &rx_buffer[1], 1, 1000);

	if(state != HAL_OK)
	{
		return 0;
	}

	if(rx_buffer[1] == 0x3A)
	{
		return SI7021_OK;
	}

	return 0;

}

float SI7021_Read_Temperature()
{
	uint8_t rx_buffer[2] = {0,0};

	uint8_t state = HAL_I2C_Mem_Read(&hi2c1, SI7021_SLAVE_ADDR, SI7021_TEMPERATURE_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 2, 1000);

	if(state != HAL_OK)
	{
		return 0;
	}

	uint16_t temp_raw = (rx_buffer[0] << 8) | (rx_buffer[1]);

	float temp = ((175.72 * temp_raw)/65536)-46.85;

	return temp;
}

float SI7021_Read_Humidity(){

	uint8_t rx_buffer[2] = {0,0};

	uint8_t state = HAL_I2C_Mem_Read(&hi2c1, SI7021_SLAVE_ADDR, SI7021_HUMIDITY_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 2, 1000);

	if(state != HAL_OK)
	{
		return 0;
	}

	uint16_t humid_raw = (rx_buffer[0] << 8) | (rx_buffer[1]);

	float humid = ((125.00 * humid_raw)/65536)-6;

	return humid;

}
