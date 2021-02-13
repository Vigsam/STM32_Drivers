/*
 * SI7006.h
 *
 *  Created on: Feb 13, 2021
 *      Author: VIGNESH
 */

#ifndef INC_SI7006_H_
#define INC_SI7006_H_

#include "main.h"
#include <stdio.h>
#include <string.h>

#define SI7006_ADDR							(0x40 << 1)  //Slave Address Left Shifted by 1 bit
#define SI7006_TEMPERATURE_ADDR				0xE3
#define SI7006_HUMIDITY_ADDR				0xE5


I2C_HandleTypeDef hi2c1;

uint8_t Get_Firmwware_Version_SI7006();

float Read_Temperature_from_SI7006();

float Read_RelativeHumidity_from_SI7006();




#endif /* INC_SI7006_H_ */
