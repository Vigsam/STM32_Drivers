/*
 * MMA8652.h
 *
 *  Created on: February 15, 2021
 *      Author: VIGNESH
 */

#ifndef INC_MMA8652_H_
#define INC_MMA8652_H_

#define MMA8652_ADDR						((0x1D)<<1)
#define CONTROL_REG_1_ADDR					  0x2A
#define CONTROL_REG_2_ADDR					  0x2B
#define CONTROL_REG_3_ADDR					  0x2C
#define DATA_X_AXIS_MSB_ADDR				  0x01
#define DATA_X_AXIS_LSB_ADDR				  0x02
#define DATA_Y_AXIS_MSB_ADDR				  0x03
#define DATA_Y_AXIS_LSB_ADDR				  0x04
#define DATA_Z_AXIS_MSB_ADDR				  0x05
#define DATA_Z_AXIS_LSB_ADDR				  0x06

#define SELF_TEST_ERROR						  2
#define DATA_RATE_SELECTION_ERROR			  3
#define DATA_READ_ERROR						  5

#define OK									  1


int Is_MMA8652_Detected(void);
int MMA8652_Initialize(void);
uint16_t GET_X_Axis(void);
uint16_t GET_Y_Axis(void);
uint16_t GET_Z_Axis(void);



#endif /* INC_MMA8652_H_ */
