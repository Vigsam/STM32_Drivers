/*
 * stm_lcd.c
 *
 *  Created on: December 4, 2021
 *      Author: VIGNESHWARAN
 */



#include "stm_lcd.h"

/*Private Prototype Definitions, These won't available to call in main function file*/

static void LCD_Write_4_bits(uint8_t val);
static void LCD_Enable(void);


/* Prototype 1: LCD Initialization */

void LCD_Init(void){

//1. Configure the GPIO Pins which are used for LCD Connections

	//a. Control Pins

	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_RS_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_RW_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_EN_PIN, GPIO_PIN_RESET);

	//b. Data Pins

	HAL_GPIO_WritePin(LCD_GPIO_DATA_PORT, LCD_GPIO_D4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_DATA_PORT, LCD_GPIO_D5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_DATA_PORT, LCD_GPIO_D6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_DATA_PORT, LCD_GPIO_D7, GPIO_PIN_RESET);

	HAL_Delay(50);

//2. Do the LCD Initialization

	 /* RS = 0 for LCD Command, RW = 0 due to writing LCD */

	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_RS_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_RW_PIN, GPIO_PIN_RESET);

	LCD_Write_4_bits(0x03);
	HAL_Delay(5);

	LCD_Write_4_bits(0x03);
	HAL_Delay(1);

	LCD_Write_4_bits(0x03);
	LCD_Write_4_bits(0x02);

	//Function Set Command

	LCD_Send_Command(LCD_CMD_4DL_2N_5X8F);


	//Display ON/OFF Control

	LCD_Send_Command(LCD_CMD_DON_CURON);

	//Display Clear

	LCD_Display_Clear();

	//Entry Mode Set

	LCD_Send_Command(LCD_CMD_INCADD);


}

/* Prototype 2: LCD Write 4 Bits (** Private **) */

static void LCD_Write_4_bits(uint8_t val){

	HAL_GPIO_WritePin(LCD_GPIO_DATA_PORT, LCD_GPIO_D4, ((val>>0) & 0x1));
	HAL_GPIO_WritePin(LCD_GPIO_DATA_PORT, LCD_GPIO_D5, ((val>>1) & 0x1));
	HAL_GPIO_WritePin(LCD_GPIO_DATA_PORT, LCD_GPIO_D6, ((val>>2) & 0x1));
	HAL_GPIO_WritePin(LCD_GPIO_DATA_PORT, LCD_GPIO_D7, ((val>>3) & 0x1));

	LCD_Enable();
}

/* Prototype 3: LCD Enable (** Private **)*/

static void LCD_Enable(void){

	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_EN_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_EN_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
}

/* Prototype 4: LCD Send Command 0 */

void LCD_Send_Command(uint8_t cmd){

	/* RS=0 for LCD Command */

	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_RS_PIN, GPIO_PIN_RESET);

	/* R/W=0 for Write */

	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_RW_PIN, GPIO_PIN_RESET);

	LCD_Write_4_bits(cmd >> 4);			//Higher Nibble
	LCD_Write_4_bits(cmd & 0x0F);		//Lower Nibble

}

/* Prototype 5: LCD Send Char*/

void LCD_Send_Char(uint8_t data){

	/* RS = 1 for LCD Data*/

	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_RS_PIN, GPIO_PIN_SET);

	/* R/W = 0 for Write */

	HAL_GPIO_WritePin(LCD_GPIO_CTRL_PORT, LCD_GPIO_RW_PIN, GPIO_PIN_RESET);

	LCD_Write_4_bits(data >> 4);			//Higher Nibble
	LCD_Write_4_bits(data & 0x0F);			//Lower Nibble
}

/* Prototype 6: LCD Send String */

void LCD_Send_String(char *message)
{
	do{
		LCD_Send_Char((uint8_t)*message++);
	}
	while(*message != '\0');
}


/* Prototype 7: LCD Clear */

void LCD_Display_Clear(void){

	/* LCD Clear Command */

	LCD_Send_Command(LCD_CMD_DISPLAY_CLEAR);
	HAL_Delay(2);

}

/* Prototype 8 : Display Return Home*/

void LCD_Display_Return_Home(void){

	/*LCD Return Home Command*/

	LCD_Send_Command(LCD_CMD_DISPLAY_RETURN_HOME);
	HAL_Delay(2);

}

/*Prototype 9: LCD Set Cursor*/

void LCD_Set_cursor(uint8_t row, uint8_t col){

	col--;
	switch(row){

	case 1:

		LCD_Send_Command((col |= 0x80));
		break;

	case 2:

		LCD_Send_Command((col |= 0xC0));
		break;

	default:
		break;
	}

}
