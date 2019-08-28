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
	int state;
	GPIO_TypeDef* led_GPIOx;
	uint16_t led_GPIO_Pin;
public:
	Led(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
	int setOn();
	int setOff();
	int setFlash();
	void interrut_toutine();
};

#endif /* STM32_LED_HPP_ */
