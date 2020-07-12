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
extern "C" void MX_RTC_Init();
const uint32_t i2cTimeout = 1000;
char helloWorld0[] = "CycleCounter0";
char Hex32B[] = "00000000";
char Hex32B2[] = "00000000";
char Hex32B3[] = "00000000";
char timetext[] = "00:00:00";
uint32_t Interrupt_counter;
uint16_t cycle = 0;

RTC_TimeTypeDef time_cs = { 0 };
RTC_DateTypeDef date_cs = { 0 };
uint32_t Address = 0x08080000;
uint32_t Address2 = 0x08080040;

void convertNrToStr(char *str, const uint8_t len, const uint32_t nr,
		const uint8_t power) {
	uint32_t nr_temp = nr;
	for (uint8_t i = 1; i <= len; ++i) {
		str[len - i] = 0x30 + (nr_temp % power);
		if (str[len - i] > 0x39) {
			str[len - i] += 7;
		}
		nr_temp = nr_temp / power;
	}

}

void usermain_init() {
	DBGMCU->CR = 7;
	if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != 0) {
		if(__HAL_RTC_ALARM_GET_FLAG(&hrtc, RTC_FLAG_ALRAF) != 0U)//Wakeup from AlarmA --> Status Flag is in Backup Domain.
		{
			uint32_t i = HAL_RTCEx_BKUPRead(&hrtc, 0);
			i++;
			//Interrupt_counter = i<<16;
			HAL_RTCEx_BKUPWrite(&hrtc, 0, i);
			__HAL_RTC_ALARM_CLEAR_FLAG(&hrtc, RTC_FLAG_ALRAF);
		}
		/* Clear Standby flag */
		HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);

	}
	if (HAL_NVIC_GetPendingIRQ(RTC_IRQn)) {
		uint32_t i = HAL_RTCEx_BKUPRead(&hrtc, 0);
		i++;
		//Interrupt_counter = i<<16;
		HAL_RTCEx_BKUPWrite(&hrtc, 0, i);
		HAL_NVIC_ClearPendingIRQ(RTC_IRQn);
	}
	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
//	if(HAL_RTCEx_BKUPRead(&hrtc, 0) == 0)
//	{
//		MX_RTC_Init();
//		HAL_RTC_SetTime(&hrtc, &time_cs, RTC_HOURFORMAT_24);
//		HAL_RTCEx_BKUPWrite(&hrtc, 0, 1);//Set BackupRegister 1 so RTC wont be initialized again
//	}
	//__HAL_LOCK(&hrtc);
//	__HAL_RTC_WRITEPROTECTION_DISABLE(&hrtc);
//	__HAL_RTC_ALARM_ENABLE_IT(&hrtc, RTC_IT_ALRA);
//	__HAL_RTC_WRITEPROTECTION_ENABLE(&hrtc);
	//__HAL_UNLOCK(&hrtc);
	uint32_t i = HAL_RTCEx_BKUPRead(&hrtc, 0);
	Interrupt_counter = i << 16;
	HAL_RTC_MspInit(&hrtc); // Needed if RTC is not in Reset State
	if (1==0) {
		time_cs.Hours = 23;
		time_cs.Minutes = 59;
		time_cs.Seconds = 50;
		HAL_RTC_SetTime(&hrtc, &time_cs, RTC_HOURFORMAT_24);
		RTC_AlarmTypeDef sAlarm = { 0 };
		sAlarm.AlarmTime.Hours = 0x0;
		sAlarm.AlarmTime.Minutes = 0x0;
		sAlarm.AlarmTime.Seconds = 0x0;
		sAlarm.AlarmTime.SubSeconds = 0x0;
		sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
		sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
		sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY | RTC_ALARMMASK_HOURS
				| RTC_ALARMMASK_MINUTES;
		sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
		sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
		sAlarm.AlarmDateWeekDay = 0x1;
		sAlarm.Alarm = RTC_ALARM_A;
		if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK) {
			Error_Handler();
		}
	}

	helloWorld0[12] = 0x30;
	oled.init();
	oled.clear();
	oled.drawString(helloWorld0, 0, 0);
	oled.drawString("Hello World!!!", 0, 8);

	oled.drawString(timetext, 0, 24);
	oled.show();
	uint32_t data1 = *((uint32_t*) Address);
	uint32_t data2 = *((uint32_t*) Address2);
	HAL_FLASHEx_DATAEEPROM_Unlock();
	//HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, Address, 0x12345678);
	//HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, Address2, 0xCAFEAFFE);
	HAL_FLASHEx_DATAEEPROM_Lock();

	convertNrToStr(Hex32B, 8, data1, 16);
	convertNrToStr(Hex32B2, 8, data2, 16);

	oled.drawString(Hex32B, 0, 16);
	oled.drawString(Hex32B2, 64, 16);
	oled.show();

}
void usermain_loop() {
	HAL_RTC_WaitForSynchro(&hrtc);
	HAL_RTC_GetTime(&hrtc, &time_cs, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &date_cs, RTC_FORMAT_BIN);

	cycle++;
	helloWorld0[12] = 0x30 + (cycle % 10);
	oled.drawString(helloWorld0, 0, 0);

	timetext[0] = (time_cs.Hours / 10) + 0x30;
	timetext[1] = (time_cs.Hours % 10) + 0x30;
	timetext[3] = (time_cs.Minutes / 10) + 0x30;
	timetext[4] = (time_cs.Minutes % 10) + 0x30;
	timetext[6] = (time_cs.Seconds / 10) + 0x30;
	timetext[7] = (time_cs.Seconds % 10) + 0x30;
	oled.drawString(timetext, 0, 24);

	convertNrToStr(Hex32B3, 8, cycle | Interrupt_counter, 16);
	oled.drawString(Hex32B3, 64, 24);
	oled.show();
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);	//Clear Wakeup Flag
	HAL_PWR_EnterSTANDBYMode();	//Enter Standby Mode
	if (HAL_NVIC_GetPendingIRQ(RTC_IRQn)) {
		uint32_t i = HAL_RTCEx_BKUPRead(&hrtc, 0);
		i++;
		//Interrupt_counter = i<<16;
		HAL_RTCEx_BKUPWrite(&hrtc, 0, i);
		//RTC->BKP0R = i;
		HAL_NVIC_ClearPendingIRQ(RTC_IRQn);
	}
	HAL_NVIC_SystemReset();
}

void twi_init() {
}
void twi_wait() {
}

//HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
//HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
void twi_write(uint8_t address, uint8_t *data, uint8_t length,
		void (*callback)(uint8_t, uint8_t*)) {
	static HAL_StatusTypeDef state;
	state = HAL_I2C_Master_Transmit(&hi2c1, address * 2, data, length,
			i2cTimeout);
	UNUSED(state);
}

#define MIN(a,b) ((a>b)?b:a)
void twi_read(uint8_t address, uint8_t length,
		void (*callback)(uint8_t, uint8_t*)) {
	uint8_t data[64];
	uint8_t len = MIN(length, 64);
	HAL_I2C_Master_Receive(&hi2c1, address * 2 + 1, data, len, i2cTimeout);

	callback(len, data);
}
