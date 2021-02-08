/*
 * dht.h
 *
 *  Created on: Feb 8, 2021
 *      Author: Vigneshwaran and janakiraman
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_

#include "main.h"

#define DHT11				1
#define DHT22				2

#define HUMIDITY			3
#define TEMPERATURE 		4

#define DHT_PORT			GPIOA
#define DHT_PIN				GPIO_PIN_1
#define DHT_TYPE			DHT22


/*Function prototype 1: Delay in Microseconds*/

void Delay_In_Microseconds(uint16_t micro_secs);

/*Function prototype 2: Set pin as an output*/

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/*Function prototype 3: Set pin as an Input*/

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/*Function prototype 4: Starting DHT*/

void DHT_Start(int dht_type);

/*Function prototype 5: Check the response from DHT*/

uint8_t DHT_Check_Response(void);

/*Function prototype 6: Reading DHT Values*/

uint8_t DHT_Read(void);

/*Function prototype 7: Reading from DHT Sensor*/

float Read_from_DHT22(int v);

/*Function prototype 8: Reading from DHT Sensor*/

float Read_from_DHT11(int v);



#endif /* INC_DHT_H_ */
