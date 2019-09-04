/*
 * stm32_led.hpp
 *
 *  Created on: 2019/08/25
 *      Author: shimizu issei
 */

#ifndef STM32_LED_HPP_
#define STM32_LED_HPP_
#include "main.h"

class Led {
private:
	enum {
		LED_ON,
		LED_OFF,
		LED_FLASH
	} state;
	GPIO_TypeDef* led_GPIOx;
	uint16_t led_GPIO_Pin;
public:
	Led(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
	void setOn();
	void setOff();
	void setFlash();
	void interrut_toutine();
};

#endif /* STM32_LED_HPP_ */
