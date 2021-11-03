/*
 * BH1745.h
 *
 *  Created on: Nov 3, 2021
 *      Author: VIGNESHWARAN
 */

#ifndef BH1745_INC_BH1745_H_
#define BH1745_INC_BH1745_H_

#include "main.h"

I2C_HandleTypeDef hi2c1;

#define	 BH1745_SLAVE_ADDR				(0x38<<1)		// Slave Address
#define  BH1745_CTRL_REG_ADDR			  0x40			// Control Register Address
#define	 BH1745_MODE_CTRL1				0x41			// Mode control register 1 address
#define	 BH1745_MODE_CTRL2				0x42			// Mode control register 2 address
#define  BH1745_MODE_CTRL3				0x44			// Mode control register 3 address
#define  BH1745_RED_LSB					0x50			// Red LSB
#define  BH1745_RED_MSB					0x51			// Red MSB
#define  BH1745_GREEN_LSB				0x52			// Green LSB
#define  BH1745_GREEN_MSB				0x53			// Green MSB
#define	 BH1745_BLUE_LSB				0x54			// Blue LSB
#define  BH1745_BLUE_MSB				0x55			// Blue MSB
#define  BH1745_ID_ADDR					0x92			// Manufacture ID Address

#define  BH1745_MEASURE_TIME_160			0x00			// Measurement Time 160 Ms
#define  BH1745_MEASURE_TIME_320			0x01			// Measurement Time 320 Ms
#define  BH1745_MEASURE_TIME_640			0x02			// Measurement Time 640 Ms
#define  BH1745_MEASURE_TIME_1280			0x03            // Measurement Time 1280 Ms
#define  BH1745_MEASURE_TIME_2560			0x04			// Measurement Time 2560 Ms
#define  BH1745_MEASURE_TIME_5120			0x05			// Measurement Time 5120 Ms

#define  BH1745_MEASURE_DELAY_160			160				// Measurement Time Delay 160 Ms
#define  BH1745_MEASURE_DELAY_320			320				// Measurement Time Delay 320 Ms
#define  BH1745_MEASURE_DELAY_640		    640				// Measurement Time Delay 640 Ms
#define  BH1745_MEASURE_DELAY_1280			1280            // Measurement Time Delay 1280 Ms
#define  BH1745_MEASURE_DELAY_2560			2560			// Measurement Time Delay 2560 Ms
#define  BH1745_MEASURE_DELAY_5120			5120			// Measurement Time Delay 5120 Ms

#define BH1745_ADC_GAIN_1X		0x10
#define BH1745_ADC_GAIN_2X		0x11
#define BH1745_ADC_GAIN_16X		0x12

uint8_t BH1745_Reset();
uint8_t BH1745_Initialize();
uint8_t BH1745_Set_Measurement_time(uint8_t measure_time);
uint8_t BH1745_Activate_Measurement(uint8_t adc_gain);
uint16_t BH1745_GetData_Red(uint32_t delay);
uint16_t BH1745_GetData_Green(uint32_t delay);
uint16_t BH1745_GetData_Blue(uint32_t delay);


#endif /* BH1745_INC_BH1745_H_ */
