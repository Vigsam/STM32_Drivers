/*
 * BH1745.h
 *
 *  Created on: Feb 16, 2021
 *      Author: VIGNESH
 */

#ifndef INC_BH1745_H_
#define INC_BH1745_H_

I2C_HandleTypeDef hi2c1;

#define BH1745_ADDR						((0x38)<<1)
#define MANUFAC_ID_ADDR					(0x92)
#define SYS_CNTRL_ADDR					(0x40)
#define MODE_CONTROL1_ADDR				(0x41)
#define MODE_CONTROL2_ADDR				(0x42)
#define MODE_CONTROL3_ADDR				(0x44)
#define RED_DATA_LSB_ADDR				(0x50)
#define RED_DATA_MSB_ADDR				(0x51)
#define GREEN_DATA_LSB_ADDR				(0x52)
#define GREEN_DATA_MSB_ADDR				(0x53)
#define BLUE_DATA_LSB_ADDR				(0x54)
#define BLUE_DATA_MSB_ADDR				(0x55)

#define OK								1

int Reset_BH1745(void);
int Initialize_BH1745(void);
int set_measurement_time(void);
int activate_measument(void);
uint16_t Read_RedData(void);
uint16_t Read_GreenData(void);
uint16_t Read_BlueData(void);

#endif /* INC_BH1745_H_ */
