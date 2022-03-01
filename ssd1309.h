/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* SSD1309 LIB Header */
/**
  ******************************************************************************
  * @file           : ssd1309.h
  * @brief          : librery
  ******************************************************************************
  * @     : mohammad amin javadi
  * Email : mohammadamin.javadi@gmail.com
  * skype : @armnxp
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/

#define        MAX_COL		128
#define        MAX_ROW		64

#define	   ADDR_MODE	0 //0:horizontal, 1:vertical, 2:page

//#define __HXT         (12000000UL)  /*!< High Speed External Crystal Clock Frequency */

//=================================
//  I/O define
//=================================
#define	GLCD_DATA_PORT 				GPIOA->ODR		/*data bus*/

#define DC_HI 						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);			/*data/instruction HI*/
#define DC_LO 						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);		/*data/instruction LOW*/

#define Reset_HI					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);		/* reset HI  */
#define Reset_LO					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);		/* reset LOW */

#define CS_HI						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);			/*chip1 HI*/
#define CS_LO						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);		/*chip1 LOW*/

#define Enable_HI					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);			/*enable HI*/
#define Enable_LO					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);		/*enable LOW*/

#define RW_HI						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);			/*read/write HI*/
#define RW_LO						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);		/*read/write LOW*/

typedef unsigned char       	B8;		/*8BIT*/

#define PROGMEM /* empty */
#define pgm_read_byte(x) (*(x))
#define pgm_read_word(x) (*(x))
#define pgm_read_float(x) (*(x))
/* USER CODE END Includes */

static const char  font[241][5] =			// small 5x7 font
{
	/* Add to small 5x7 font */
}

/* Private function prototypes -----------------------------------------------*/

void Write_Cmd(unsigned char cmd);
void Write_Data(unsigned char dat);
void Set_Addr(B8 page, B8 lCol, B8 hCol);
void Set_PageAddr(B8 star, B8 end);
void Set_ColAddr(B8 star, B8 end);
void Home_Addr(void);
void clear();
void Show_pic(unsigned char arr[][MAX_COL]);
void Show_pic2(unsigned char pic[8][128]);
void delay_100us(unsigned char d);
void delay_100us(unsigned char d);
void delay_s(unsigned char d);
void Initial_SSD1309(void);
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

#endif /* __MAIN_H */