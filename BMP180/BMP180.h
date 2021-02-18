/*
 * BMP180.h
 *
 *  Created on: Feb 17, 2021
 *      Author: VIGNESH
 */

#ifndef INC_BMP180_H_
#define INC_BMP180_H_

#include "main.h"
#include <stdio.h>
#include <stdint.h>

I2C_HandleTypeDef hi2c2;

#define BMP180_ADDR							((0x77) << 1)
#define BMP180_CHIP_ID_ADDR					(0xD0)
#define BMP180_RESET_REG_ADDR				(0xE0)
#define BMP180_CONTROL_REG_ADDR				(0xF4)
#define BMP180_MSB_ADDR						(0xF6)
#define BMP180_LSB_ADDR						(0xF7)
#define BMP180_XLSB_ADDR					(0xF8)
#define BMP180_COEFFIECIENT_ADDR			(0xAA)

#define OK									1

int Initialize_BMP180(void);
int Reset_BMP180(void);
int16_t Read_Calibration_Co_effiecients(void);
long Read_Uncompensated_Temperature_from_BMP180(void);
float Read_Temperature_from_BMP180 (void);
long Read_Uncompensated_Pressure(int oss);
float Read_Pressure_from_BMP180(int oss);
float Read_Altitude_from_BMP180(void);
void BMP180_Start(void);


#endif /* INC_BMP180_H_ */
