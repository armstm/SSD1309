/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* SSD1309 LIB Header */
/**
  ******************************************************************************
  * @file           : ssd1309.h
  * @brief          : MAIN .C
  ******************************************************************************
  * @     : mohammad amin javadi
  * Email : mohammadamin.javadi@gmail.com
  * skype : @armnxp
  ******************************************************************************
  */
 /* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdlib.h>
#include <string.h>
#INCLUDE "ssd1309.h"

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();

	/* Initialize all OLD  peripherals */
	delay_100us(10);
	Initial_SSD1309();
	Home_Addr();
	clear();	

  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	
		Set_PageAddr(0xB0,0xB0);	 /* set addres page 0xB0 ... 0XB7  */
		Set_ColAddr(0x03,0x10);      /* set COL    ADDR 0x00 ... 0X0F LOWER  */
									 /* set COL    ADDR 0x10 ... 0X1F UPPER  */
		
		sprintf(str," Hello Word! %d",03012022); /* STRING PRINT  WHIT SPRINTF */
		print(str);
		
    /* USER CODE BEGIN 3 */
  }
}
/*#############################################################################
################# high level functions for user interaction ###################
#############################################################################*/
void putc(unsigned char aChar)
{
	unsigned int i;

	if((aChar >= 0x20) && (aChar <= 0x7E))	// normal ASCII Char
	{
		aChar -= 0x20;						// subtract to match index
	}
	else if (aChar >= 0xA0)					// extended UTF8 char
	{
		aChar -= 0x41;						// subtract to match index
	}
	else									// char not available
	{
		aChar = '?' - 0x20;					// make a ?
	}


	for(i=0;i<5;i++)
	{
		Write_Data(pgm_read_byte(&font[aChar][i]));
	}
	Write_Data(0);
}

void print(char *aString)
{
	char * Src_Pointer = aString;			// copy the pointer, because will will increment it

	while(*Src_Pointer != '\0')				// until string end
	{
		putc((unsigned char)*Src_Pointer);
		Src_Pointer++;
	}
}

void Write_Cmd(unsigned char cmd)
{
	unsigned int arr_cmd[8];

	CS_LO;
	DC_LO;
	RW_LO;
	GPIOA->ODR = (cmd&0xff);
	Enable_HI;
	Enable_LO;
	CS_HI;
	//delay_ms(10);

}

void Write_Data(unsigned char dat)
{
	unsigned int arr_dat[8];

	CS_LO;
	DC_HI;
	RW_LO;
	GPIOA->ODR = (dat&0xff);
	Enable_HI;
	Enable_LO;
	CS_HI;
	//delay_ms(10);
}

#if (ADDR_MODE==2)
void Set_Addr(B8 page, B8 lCol, B8 hCol)
{
	Write_Cmd(page);//Set Page Start Address
	//Write_Cmd(lCol);//Set Lower Column Start Address
	Write_Cmd(hCol);//Set Higher Column Start Address
	Write_Cmd(lCol);//Set Lower Column Start Address
}
#else
void Set_PageAddr(B8 star, B8 end)
{
	Write_Cmd(star);
	Write_Cmd(end);
}
void Set_ColAddr(B8 star, B8 end)
{
	Write_Cmd(star);
	Write_Cmd(end);
}
#endif

void Home_Addr(void)
{
		//Write_Cmd(ADDR_MODE);
		#if (ADDR_MODE<2)
		Write_Cmd(0x22);//Set Page Address
		Set_PageAddr(0,7);
		Write_Cmd(0x21);//Set Column Address
		Set_ColAddr(0,127);
	#else
		Set_Addr(0xb0,0,0x10);
	#endif
}

//=========================================
void clear()//clear
{
B8 x,y;
	//Home_Addr();
for(x = 0;x<8;x++)
 {
   for(y = 0;y<128;y++)
      {
				Write_Data(0x00);
      }
 }
}

void Show_pic(unsigned char arr[][MAX_COL])
{
	unsigned char i=0,j=0;
	//Home_Addr();
	for (i = 0;i<MAX_ROW/8;i++)
	{
		#if (ADDR_MODE==2)
			Set_Addr(0xb0+i,0x00,0x10);
		#endif
		for (j = 0;j<128;j++){
			Write_Data(~arr[i][j]);
		}
	}
	delay_s(1);
}

void Show_pic2(unsigned char pic[8][128])
{
	unsigned char i=0,j=0;
	//Home_Addr();
	for (i = 0;i<MAX_ROW/8;i++)
	{
		#if (ADDR_MODE==2)
			Set_Addr(0xb0+i,0,0x10);
		#endif
		for (j = 0;j<128;j++){
			Write_Data(pic[i][j]);
		}
	}
	delay_s(1);
}

void delay_100us(unsigned char d)		//12MHz_us
{
	unsigned char  i=0,j=0;

	for(j=0;j<d;j++)
	{
		for(i=0;i<100;i++)
		{}
	}
}

void delay_ms(unsigned char d)		//12MHz_us
{
	unsigned char j=0;

	for(j=0;j<d;j++)
	{
		delay_100us(10);
	}
}

void delay_s(unsigned char d)		//12MHz_us
{
	unsigned char x=0,y=0,j=0;

	for(j=0;j<d;j++)
	{
		for(x=0;x<100;x++)
	    	{
	     		for(y=0;y<10;y++)
	      		{
				delay_ms(1);
	     		}
	    	}
	}
}

void Initial_SSD1309(void)
{
	Reset_HI;
	Write_Cmd(0xae);//Set Display ON/OFF =>0xae:Display off

	Write_Cmd(0x20);//Set Memory Addressing Mode
	Write_Cmd(0x00);

	Write_Cmd(0x81);//Set contrast Control for BANK 0
	Write_Cmd(0x80);

	Write_Cmd(0x40);//Set Display Start Line
	Write_Cmd(0xa1);//Set Segment Re-map =>0xa0:column addr. 0 is mapped to SEG0
	Write_Cmd(0xa4);//Entire Display On =>0xa4:resume to RAM content display
	Write_Cmd(0xa6);//Set Normal/Inverse Display =>0xa6:Normal,0xa7:inverse

	Write_Cmd(0xa8);//Set Multiplex Ratio
	Write_Cmd(0x3f);//63 --- 0x3f > 1/64 duty --- 0x1f > 1/32 duty

	Write_Cmd(0xad);//Master Configuration
	Write_Cmd(0x8e);

	Write_Cmd(0xc8);//Set COM Output Scan Direction =>0xc0:scan from COM0 to COM63, 0xc8:scan from COM63 to COM0

	Write_Cmd(0xd3);//Set Display Offset
	Write_Cmd(0x00);

	Write_Cmd(0xd5);//Set Display Clock Divid Ratio/Oscillator Frequency
	Write_Cmd(0xf0);

	Write_Cmd(0xd8);//Set Area Color Mode ON/OFF & Low Power Display Mode
	Write_Cmd(0x05);//0x05:monochrome mode and low power display mode

	Write_Cmd(0xd9);//Set Pre-charge Period
	Write_Cmd(0xf1);

	Write_Cmd(0xda);//Set COM Pins Hardware Configuration
	Write_Cmd(0x12);

	Write_Cmd(0xdb);//Set Vcomh Deselect Level
	Write_Cmd(0x40);

	Write_Cmd(0x2e);//deactivate scroll

	Write_Cmd(0xaf);//Set Display ON/OFF =>0xaf:Display on
}

