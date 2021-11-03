/*
 * BH1745.c
 *
 *  Created on: Nov 3, 2021
 *      Author: VIGNESHWARAN
 */


#include "BH1745.h"


uint8_t BH1745_Reset(){

uint8_t status;

uint8_t tx_buffer = 0x8B;

uint8_t rx_buffer;

status = HAL_I2C_Mem_Write(&hi2c1, BH1745_SLAVE_ADDR, BH1745_CTRL_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, HAL_MAX_DELAY);

if(status != HAL_OK){

	return 0;

}

status = HAL_I2C_Mem_Read(&hi2c1, BH1745_SLAVE_ADDR, BH1745_CTRL_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &rx_buffer, 1, HAL_MAX_DELAY);

if(rx_buffer == 0x0B){

	return HAL_OK;
}

return 0;

}

uint8_t BH1745_Initialize(){

uint8_t rx_buffer;

HAL_I2C_Mem_Read(&hi2c1, BH1745_SLAVE_ADDR, BH1745_ID_ADDR, I2C_MEMADD_SIZE_8BIT, &rx_buffer, 1, HAL_MAX_DELAY);

if(rx_buffer == 0xE0)
{
	return HAL_OK;
}

return 0;

}

uint8_t BH1745_Set_Measurement_time(uint8_t measure_time){

uint8_t status = HAL_I2C_Mem_Write(&hi2c1, BH1745_SLAVE_ADDR, BH1745_MODE_CTRL1, I2C_MEMADD_SIZE_8BIT, &measure_time, 1 , HAL_MAX_DELAY);

if(status != HAL_OK)
{
	return 0;
}

HAL_I2C_Mem_Read(&hi2c1, BH1745_SLAVE_ADDR, BH1745_MODE_CTRL1, I2C_MEMADD_SIZE_8BIT, &measure_time, 1 , HAL_MAX_DELAY);

if(measure_time == BH1745_MEASURE_TIME_160)
{
	return HAL_OK;
}

else if(measure_time == BH1745_MEASURE_TIME_320)
{
	return HAL_OK;
}

else if(measure_time == BH1745_MEASURE_TIME_640)
{
	return HAL_OK;
}

else if(measure_time == BH1745_MEASURE_TIME_1280)
{
	return HAL_OK;
}

else if(measure_time == BH1745_MEASURE_TIME_2560)
{
	return HAL_OK;
}

else if(measure_time == BH1745_MEASURE_TIME_5120)
{
	return HAL_OK;
}

return 0;

}

uint8_t BH1745_Activate_Measurement(uint8_t adc_gain){

uint8_t tx_buffer = 0x02;

uint8_t status;

status = HAL_I2C_Mem_Write(&hi2c1, BH1745_SLAVE_ADDR, BH1745_MODE_CTRL2, I2C_MEMADD_SIZE_8BIT, &adc_gain, 1 , HAL_MAX_DELAY);

if(status != HAL_OK)
{
	return 0;
}

status = HAL_I2C_Mem_Write(&hi2c1, BH1745_SLAVE_ADDR, BH1745_MODE_CTRL3, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1 , HAL_MAX_DELAY);

if(status != HAL_OK)
{
	return 0;
}

HAL_I2C_Mem_Read(&hi2c1, BH1745_SLAVE_ADDR, BH1745_MODE_CTRL2, I2C_MEMADD_SIZE_8BIT, &adc_gain, 1 , HAL_MAX_DELAY);

if(adc_gain == BH1745_ADC_GAIN_1X)
{
	return HAL_OK;
}

if(adc_gain == BH1745_ADC_GAIN_2X)
{
	return HAL_OK;
}

if(adc_gain == BH1745_ADC_GAIN_16X)
{
	return HAL_OK;
}

return 0;

}

uint16_t BH1745_GetData_Red(uint32_t delay)
{
	uint8_t rx_buffer[2] = {0,0};

	uint16_t reg_value;

	uint8_t status = HAL_I2C_Mem_Read(&hi2c1, BH1745_SLAVE_ADDR, BH1745_RED_LSB, I2C_MEMADD_SIZE_8BIT, rx_buffer, 2 , delay);

	if(status != HAL_OK)
	{
		return 0;
	}

	reg_value = ((rx_buffer[1] << 8) | (rx_buffer[0]));

	return reg_value;
}

uint16_t BH1745_GetData_Green(uint32_t delay)
{
	uint8_t rx_buffer[2] = {0,0};

	uint16_t reg_value;

	uint8_t status = HAL_I2C_Mem_Read(&hi2c1, BH1745_SLAVE_ADDR, BH1745_GREEN_LSB, I2C_MEMADD_SIZE_8BIT, rx_buffer, 2 , delay);

	if(status != HAL_OK)
	{
		return 0;
	}

	reg_value = ((rx_buffer[1] << 8) | (rx_buffer[0]));

	return reg_value;

	return 0;
}

uint16_t BH1745_GetData_Blue(uint32_t delay)
{
	uint8_t rx_buffer[2] = {0,0};

	uint16_t reg_value;

	uint8_t status = HAL_I2C_Mem_Read(&hi2c1, BH1745_SLAVE_ADDR, BH1745_BLUE_LSB, I2C_MEMADD_SIZE_8BIT, rx_buffer, 2 , delay);

	if(status != HAL_OK)
	{
		return 0;
	}

	reg_value = ((rx_buffer[1] << 8) | (rx_buffer[0]));

	return reg_value;
}
