/*
 * SI7006.c
 *
 *  Created on: Feb 13, 2021
 *      Author: VIGNESH
 */

#include "SI7006.h"

I2C_HandleTypeDef hi2c1;

uint8_t v_rx_buff[2] = {0,0};

/*Function prototype 1: Get the firmware version of SI7006*/

uint8_t Get_Firmwware_Version_SI7006()
{
	uint8_t state;



	state = HAL_I2C_Mem_Read(&hi2c1, SI7006_ADDR, 0x84B8, I2C_MEMADD_SIZE_16BIT, v_rx_buff, 1, 100);

	if(state != HAL_OK)
	{

		return 0;
	}

	if((v_rx_buff[0] == 0x20) || (v_rx_buff[0] == 0xFF))
	{
		return (int)v_rx_buff;
	}

	return 0;
}

/*Function Prototype 2: Read Temperature from SI7006*/

float Read_Temperature_from_SI7006()
{
	uint8_t state;

	uint8_t rx_buff[2] = {0,0};

	float temperature;

	uint16_t Value;

	state = HAL_I2C_Mem_Read(&hi2c1, SI7006_ADDR, SI7006_TEMPERATURE_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buff , 1, HAL_MAX_DELAY);

	if(state != HAL_OK)
	{
		return 0;
	}

	Value = rx_buff[0] << 8 | rx_buff[1];

	temperature = ((175.72 * Value)/ 65536) - 46.85;

	return temperature;

}

/*Function Prototype 3: Read Humidity from SI7006*/

float Read_RelativeHumidity_from_SI7006()
{

	int state;

	float humidity;

	uint16_t Value;

	uint8_t rx_buffer[2];

	state = HAL_I2C_Mem_Read(&hi2c1, SI7006_ADDR, SI7006_HUMIDITY_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer, sizeof(rx_buffer), HAL_MAX_DELAY);

	if(state != HAL_OK)
	{

		return -1;
	}

	Value = (rx_buffer[0] << 8) | rx_buffer[0];

	humidity = ((125 * Value)/65536)-6;

	return humidity;
}
