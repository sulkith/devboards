/*
 * usermain.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: sulkith
 */
#include "usermain.hpp"
#include "main.h"
#include "SSD1306-AVR/Framebuffer.h"

Framebuffer oled;
extern I2C_HandleTypeDef hi2c1;
extern RTC_HandleTypeDef hrtc;
const uint32_t i2cTimeout = 1000;
char helloWorld0[] = "CycleCounter0";
char Hex32B[] = "00000000";
char Hex32B2[] = "00000000";
char Hex32B3[] = "00000000";
char timetext[] = "00:00:00";
uint16_t cycle = 0;

RTC_TimeTypeDef time_cs = {0};
RTC_DateTypeDef date_cs = {0};
uint32_t Address = 0x08080000;
uint32_t Address2 = 0x08080040;

void convertNrToStr(char* str, const uint8_t len, const uint32_t nr, const uint8_t power)
{
	uint32_t nr_temp= nr;
	for(uint8_t i = 1; i<=len;++i)
	{
		str[len-i] = 0x30+(nr_temp%power);
		if(str[len-i] >0x39)
		{
			str[len-i] += 7;
		}
		nr_temp = nr_temp / power;
	}

}

void usermain_init()
{
	if(HAL_RTCEx_BKUPRead(&hrtc, 0) == 0)
	{

		HAL_RTC_SetTime(&hrtc, &time_cs, RTC_HOURFORMAT_24);
		HAL_RTCEx_BKUPWrite(&hrtc, 0, 1);//Set BackupRegister 1 so RTC wont be initialized again
	}

	helloWorld0[12] = 0x30;
	oled.init();
	oled.clear();
	oled.drawString(helloWorld0,0,0);
	oled.drawString("Hello World!!!",0,8);


	oled.drawString(timetext,0,24);
	oled.show();
	uint32_t data1 = *((uint32_t *)Address);
	uint32_t data2 = *((uint32_t *)Address2);
	HAL_FLASHEx_DATAEEPROM_Unlock();
	//HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, Address, 0x12345678);
	//HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, Address2, 0xCAFEAFFE);
	HAL_FLASHEx_DATAEEPROM_Lock();
	uint32_t data3 = *((uint32_t *)Address);
	uint32_t data4 = *((uint32_t *)Address2);

	convertNrToStr(Hex32B, 8, data1, 16);
	convertNrToStr(Hex32B2, 8, data2, 16);

	oled.drawString(Hex32B,0,16);
	oled.drawString(Hex32B2,64,16);
	oled.show();

}
void usermain_loop()
{
	HAL_RTC_WaitForSynchro(&hrtc);
	HAL_RTC_GetTime(&hrtc, &time_cs, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &date_cs, RTC_FORMAT_BIN);

	cycle++;
	helloWorld0[12] = 0x30+(cycle%10);
	oled.drawString(helloWorld0,0,0);

	timetext[0] = (time_cs.Hours/10)+0x30;
	timetext[1] = (time_cs.Hours%10)+0x30;
	timetext[3] = (time_cs.Minutes/10)+0x30;
	timetext[4] = (time_cs.Minutes%10)+0x30;
	timetext[6] = (time_cs.Seconds/10)+0x30;
	timetext[7] = (time_cs.Seconds%10)+0x30;
	oled.drawString(timetext,0,24);

	convertNrToStr(Hex32B3, 8, cycle, 16);
	oled.drawString(Hex32B3,64,24);
	oled.show();
}

void twi_init()
{}
void twi_wait()
{}

//HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
//HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
void twi_write(uint8_t address, uint8_t* data, uint8_t length, void (*callback)(uint8_t, uint8_t *))
{
	static HAL_StatusTypeDef state;
	state = HAL_I2C_Master_Transmit(&hi2c1, address*2, data, length,i2cTimeout);
}

#define MIN(a,b) ((a>b)?b:a)
void twi_read(uint8_t address, uint8_t length, void (*callback)(uint8_t, uint8_t *))
{
	uint8_t data[64];
	uint8_t len = MIN(length,64);
	HAL_I2C_Master_Receive(&hi2c1, address*2+1, data, len,i2cTimeout);

	callback(len,data);
}
