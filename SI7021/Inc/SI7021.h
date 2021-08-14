/*
 * SI7021.h
 *
 *  Created on: August 14, 2021
 *      Author: VIGNESH
 */

#ifndef SI7021_INC_SI7021_H_
#define SI7021_INC_SI7021_H_

#include "main.h"

I2C_HandleTypeDef hi2c1;

#define SI7021_SLAVE_ADDR							((0x40)<<1)
#define SI7021_FIRMWARE_REVISION_ADDR				0x84B8
#define SI7021_TEMPERATURE_ADDR						0xE3
#define SI7021_HUMIDITY_ADDR						0xE5
#define SI7021_USER_WRITE_REG_ADDR					0xE6
#define SI7021_USER_READ_REG_ADDR					0xE7
#define SI7021_RESET_ADDR							0xFE

#define SI7021_OK									1

uint8_t SI7021_Initialization();
uint8_t SI7021_Set_Resolution();
float SI7021_Read_Temperature();
float SI7021_Read_Humidity();


#endif /* SI7021_INC_SI7021_H_ */
