/*

DS3231 RTC Library for STM32 HAL Layer Library

Author: Vigneshwaran.S, Janakiraman

Designation: Embedded IoT Developer 

*/
#include "main.h"

#include <stdio.h>
#include <stdint.h>

/*Define Address of DS3231 here*/

#define DS3231_ADDRESS 0xD0

/*Function Prototype 1: Conversion of Decimal To BCD*/

uint8_t Decimal_to_BCD(int decimal);

/*Function Prototype 2: Conversion of BCD To Decimal*/

int BCD_To_Decimal(uint8_t bcd);

/*Function Prototype 3: To Set Time*/

void Set_Time(uint8_t secs,uint8_t mins,uint8_t hrs,uint8_t dow,uint8_t dom,uint8_t month,uint8_t year);

//Define a structure to save time

typedef struct TIME{

	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;

}TIME_t;


TIME_t time;

/*Function Prototype 4: Function To Get and save Time*/

void Get_Time(void);

/*Function Prototype 5: Function to Read Temperature from DS3231*/

float Get_Temp(void);

/*Function Prototype 6: Function for Force conversion of Temperature from DS3231*/

void force_temp_conv (void);
