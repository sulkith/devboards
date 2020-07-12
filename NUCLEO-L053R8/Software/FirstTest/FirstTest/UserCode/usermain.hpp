/*
 * main.hpp
 *
 *  Created on: Jul 5, 2020
 *      Author: sulkith
 */

#ifndef USERMAIN_HPP_
#define USERMAIN_HPP_
#include "stm32l0xx_hal.h"

#ifdef __cplusplus
 extern "C" {
#endif

 extern void usermain_init();
 extern void usermain_loop();
 //extern void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);
 extern uint32_t Interrupt_counter;
#ifdef __cplusplus
 }
#endif



#endif /* USERMAIN_HPP_ */
