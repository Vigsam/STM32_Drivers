/*
 * si7021.h
 *
 *  Created on: Apr 8, 2021
 *      Author: VIGNESH
 */

#ifndef INC_SI7021_H_
#define INC_SI7021_H_

#include "main.h"

#define OK 				1

I2C_HandleTypeDef hi2c1;

#define 	SI7021_SLAVE_ADDR					((0x40) << 1)
#define 	SI7021_FIRMWARE_REV_ADDR			0x84B8
#define 	SI7021_TEMP_ADDR					0xE3
#define 	SI7021_HUM_ADDR						0xE5

uint8_t SI7021_Init();

float Read_Temperature_From_SI7021();

float Read_humidity_From_SI7021();


#endif /* INC_SI7021_H_ */
