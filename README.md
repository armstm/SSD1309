# SSD1309
SSD1309 OLD whit STM32 whit HALL libbery

LCD PART NUMBER : WEO012864JLPP3N00000
MCU PART NUMBER : STM32F103C6

The amount of RAM and the amount of FLASH used at startup:
1. RAM   1.71KB    USED - 10.69%
2. FLASH 10.75KBKB USED - 8.40%
I do it better to improve.
SSD1309 controller OLD . It is supposed to support I2C, 4 wire SPI, 6800 and 8080 parallel interfaces.
This libery support 8080 and 6800 protocol .
and used microcontroller STM32 whit HALL libbery.

set settings for port configuration:

1. define	GLCD_DATA_PORT 				GPIOA->ODR		/*data bus*/
2. define DC_HI 						    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);			/*data/instruction HI*/
3. define DC_LO 						    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);		/*data/instruction LOW*/
4. define Reset_HI					    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);		  /* reset HI  */
5. define Reset_LO					    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);		/* reset LOW */
6. define CS_HI						      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);			/*chip1 HI*/
7. define CS_LO						      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);		/*chip1 LOW*/
8. define Enable_HI					    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);			/*enable HI*/
9. define Enable_LO					    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);		/*enable LOW*/
10. define RW_HI						      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);			/*read/write HI*/
11. define RW_LO						      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);		/*read/write LOW*/


