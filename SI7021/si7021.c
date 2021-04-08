/*
 * si7021.c
 *
 *  Created on: Apr 8, 2021
 *      Author: VIGNESH
 */


#include "si7021.h"

uint8_t SI7021_Init()
{

uint8_t rx_buffer[2] = {0,0};

int state = HAL_I2C_Mem_Read(&hi2c1, SI7021_SLAVE_ADDR, SI7021_FIRMWARE_REV_ADDR, I2C_MEMADD_SIZE_16BIT, rx_buffer, 1, 1000);

if(state != HAL_OK)
{
	return 0;

}

if((rx_buffer[0] == 0x20) || (rx_buffer[0] == 0xFF))
{
	return rx_buffer[0];
}

return 0;

}


float Read_Temperature_From_SI7021()
{
	uint8_t rx_buffer[2] = {0,0};

	int state = HAL_I2C_Mem_Read(&hi2c1, SI7021_SLAVE_ADDR, SI7021_TEMP_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 1, 2000);

	float temperature;

	if(state != HAL_OK)
	{
		return 0;
	}

	uint16_t temp_code = ((rx_buffer[0]<<8) | rx_buffer[1]);

	temperature = ((175.72 * temp_code)/65536) - 46.85;

	return temperature;


}

float Read_humidity_From_SI7021()
{
	uint8_t rx_buffer[2] = {0,0};

	int state = HAL_I2C_Mem_Read(&hi2c1, SI7021_SLAVE_ADDR, SI7021_HUM_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, 1, 2000);

	float humidity;

	if(state != HAL_OK)
	{
		return 0;
	}

	uint16_t hum_code = ((rx_buffer[0]<<8) | rx_buffer[1]);

	humidity = 	((125*hum_code)/65536)-6;


	return humidity;
}
