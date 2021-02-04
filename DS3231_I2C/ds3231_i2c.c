/*

DS3231 RTC Library for STM32 HAL Layer Library

Author: Vigneshwaran, Janakiraman

Designation: Embedded IoT Developer 

*/

#include "ds3231_i2c.h"

/*Definition of I2C Handle*/

I2C_HandleTypeDef hi2c1;

/*Function Prototype 1: Conversion of Decimal To BCD*/

uint8_t Decimal_to_BCD(int decimal)
{
	return (uint8_t) ((decimal/10*16) + (decimal%10));
}

/*Function Prototype 2: Conversion of BCD To Decimal*/

int BCD_To_Decimal(uint8_t bcd)
{
	return (int) ((bcd/16*10) + (bcd%16));	
}

/*Function Prototype 3: To Set Time*/

void Set_Time(uint8_t secs,uint8_t mins,uint8_t hrs,uint8_t dow,uint8_t dom,uint8_t month,uint8_t year)
{
	uint8_t set_time[6];
	
	set_time[0] = Decimal_to_BCD(secs);
	set_time[1] = Decimal_to_BCD(mins);
	set_time[2] = Decimal_to_BCD(hrs);
	set_time[3] = Decimal_to_BCD(dow);
	set_time[4] = Decimal_to_BCD(dom);
	set_time[5] = Decimal_to_BCD(month);
	set_time[6] = Decimal_to_BCD(year);
	
	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, 1, set_time, 7, 1000);
	
}

/*Function Prototype 4: Function To Get and save Time*/

void Get_Time(void)
{

	uint8_t get_time[7];
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x00, 1, get_time, 7, 1000);
	time.seconds =  BCD_To_Decimal(get_time[0]);
	time.minutes = BCD_To_Decimal(get_time[1]);
	time.hours = BCD_To_Decimal(get_time[2]);
	time.dayofweek = BCD_To_Decimal(get_time[3]);
	time.dayofmonth = BCD_To_Decimal(get_time[4]);
	time.month = BCD_To_Decimal(get_time[5]);
	time.year = BCD_To_Decimal(get_time[6]);

}

/*Function Prototype 5: Function to Read Temperature from DS3231*/

float Get_Temp (void)
{
	uint8_t temp[2];
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x11, 1, temp, 2, 1000);
	return ((temp[0])+(temp[1]>>6)/4.0);
}

/*Function Prototype 5: Function for Force conversion of Temperature from DS3231*/

void force_temp_conv (void)
{
	uint8_t status=0;
	uint8_t control=0;
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x0F, 1, &status, 1, 100);  // read status register
	if (!(status&0x04))  // if the BSY bit is not set
	{
		HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x0E, 1, &control, 1, 100);  // read control register
		HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x0E, 1, (uint8_t *)(control|(0x20)), 1, 100);  // write modified control register with CONV bit as'1'
	}
}

