/*
 * stm_lcd.h
 *
 *  Created on: December 4, 2021
 *      Author: VIGNESHWARAN
 */

#ifndef STM_LCD_INC_STM_LCD_H_
#define STM_LCD_INC_STM_LCD_H_

#include "main.h"

/* Application Wise Configurable Items */

#define LCD_GPIO_CTRL_PORT			GPIOB
#define LCD_GPIO_DATA_PORT			GPIOA
#define LCD_GPIO_RS_PIN			    GPIO_PIN_3
#define LCD_GPIO_RW_PIN				GPIO_PIN_5
#define LCD_GPIO_EN_PIN				GPIO_PIN_4
#define LCD_GPIO_D4					GPIO_PIN_5
#define LCD_GPIO_D5					GPIO_PIN_6
#define LCD_GPIO_D6					GPIO_PIN_7
#define LCD_GPIO_D7					GPIO_PIN_8

/*LCD Commands*/

#define LCD_CMD_4DL_2N_5X8F				0x28	//4Bit Data Length, 2 Lines and 5x8 Font Size
#define LCD_CMD_DON_CURON				0x0C	//Display and Cursor ON
#define LCD_CMD_INCADD					0x06    //Increment RAM Address
#define LCD_CMD_DISPLAY_CLEAR			0x01	//Clear Display
#define LCD_CMD_DISPLAY_RETURN_HOME		0x02	//Return Home (Original Position)

/* Prototypes */

void LCD_Init(void);
void LCD_Send_Command(uint8_t cmd);
void LCD_Display_Clear(void);
void LCD_Send_String(char *message);
void LCD_Display_Return_Home(void);
void LCD_Send_Char(uint8_t data);
void LCD_Set_cursor(uint8_t row, uint8_t col);

#endif /* STM_LCD_INC_STM_LCD_H_ */
