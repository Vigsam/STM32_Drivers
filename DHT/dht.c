/*
 * dht.c
 *
 *  Created on: Feb 8, 2021
 *      Author: VIGNESH
 */

#include "dht.h"
#include <stdio.h>
#include <string.h>

/* private variables */

uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;

// Relative_humidity ---> Relative Humidity, Temp_int Temperature

uint16_t SUM, RH, TEMP;

uint8_t Presence = 0;

TIM_HandleTypeDef htim6;

/*Function prototype 1: Delay in Microseconds*/

void Delay_In_Microseconds(uint16_t micro_secs)
{


	__HAL_TIM_SET_COUNTER(&htim6, 0);
	while((__HAL_TIM_GET_COUNTER(&htim6)) < micro_secs);

}

/*Function prototype 2: Set pin as an output*/

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

}

/*Function prototype 3: Set pin as an Input*/

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

/*Function prototype 4: Starting DHT*/

void DHT_Start(int dht_type)
{

if(DHT_TYPE == DHT22)
{
	/*Generate Low Signal for 12 milliseconds*/

  Set_Pin_Output(DHT_PORT,DHT_PIN);
  HAL_GPIO_WritePin(GPIOA, DHT_PIN, 0);
  Delay_In_Microseconds(12000);

  	/*Generate High Signal for next 20 microseconds*/

  HAL_GPIO_WritePin(GPIOA, DHT_PIN, 1);
  Delay_In_Microseconds(20);
  Set_Pin_Input(DHT_PORT, DHT_PIN);
}

if(DHT_TYPE == DHT11)
{
	/*Generate Low Signal for 18 milliseconds*/

  Set_Pin_Output(DHT_PORT,DHT_PIN);
  HAL_GPIO_WritePin(GPIOA, DHT_PIN, 0);
  Delay_In_Microseconds(18000);

  	/*Generate High Signal for next 20 microseconds*/

  HAL_GPIO_WritePin(GPIOA, DHT_PIN, 1);
  Delay_In_Microseconds(20);
  Set_Pin_Input(DHT_PORT, DHT_PIN);
}

}

/*Function prototype 5: Check the response from DHT*/

uint8_t DHT_Check_Response(void)
{
	uint8_t response = 0;
	Delay_In_Microseconds(40);

	if(!(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN)))
	{
		Delay_In_Microseconds(80);
		if(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN)){ response = 1; }
		else response = -1;
	}
	while(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN));
	return response;
}

/*Function prototype 6: Reading DHT Values*/

uint8_t DHT_Read(void)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));   // wait for the pin to go high
		Delay_In_Microseconds(40);   // wait for 40 us

		if (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))   // if the pin is low
		{
			i&= ~(1<<(7-j));   // write 0
		}
		else i|= (1<<(7-j));  // if the pin is high, write 1
		while ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));  // wait for the pin to go low
	}
	return i;
}


/*Function prototype 7: Reading from DHT22 Sensor*/

float Read_from_DHT22(int v)
{
	 DHT_Start(DHT22);
	 Presence = DHT_Check_Response();
	 Rh_byte1 = DHT_Read();
	 Rh_byte2 = DHT_Read();
	 Temp_byte1 = DHT_Read();
	 Temp_byte2 = DHT_Read();
	 SUM = DHT_Read();

	 uint16_t TEMP = ((Temp_byte1<<8)|Temp_byte2);
	 uint16_t RH = ((Rh_byte1<<8)|Rh_byte2);

	 if(v == HUMIDITY)
	 {
		 float humidity = RH/10.0;
		 return humidity;
	 }

	 if (v == TEMPERATURE)
	 {
		 float temperature = TEMP/10.0;
		 return temperature;
	 }

	 else
	 {
		 return 0;
	 }
}

/*Function prototype 8: Reading from DHT11 Sensor*/

float Read_from_DHT11(int v)
{

	//	char buff1[20];
	//	char buff2[20];

	 DHT_Start(DHT11);
	 Presence = DHT_Check_Response();
	 Rh_byte1 = DHT_Read();
	 Rh_byte2 = DHT_Read();
	 Temp_byte1 = DHT_Read();
	 Temp_byte2 = DHT_Read();
	 SUM = DHT_Read();
	 HAL_Delay(2000);

	 int TEMP = Temp_byte1;
	 int RH = Rh_byte1;

	 if(v == HUMIDITY)
	 {
		 float humidity = RH;
		 return humidity;
	 }

	 if (v == TEMPERATURE)
	 {
		 float temperature = TEMP;
		 return temperature;
	 }

	 else
	 {
		 return 0;
	 }
}



