/*
 * stm32_led.cpp
 *
 *  Created on: 2019/08/25
 *      Author: shimizu issei
 */

#include"stm32_led.hpp"

Led::Led(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin) {
    led_GPIOx = GPIOx;
    led_GPIO_Pin = GPIO_Pin;
}

void Led::setOn(){
    state=LED_ON;
    HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, GPIO_PIN_SET);
}
void Led::setOff(){
    state=LED_OFF;
    HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, GPIO_PIN_RESET);
}
void Led::setFlash(){
    state=LED_FLASH;
}

void Led::interrut_toutine(){
    switch (state)
    {
    case LED_ON:
        HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, GPIO_PIN_SET);
        break;
    case LED_OFF:
        HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, GPIO_PIN_RESET);
        break;
    case LED_FLASH:
        HAL_GPIO_TogglePin(led_GPIOx,led_GPIO_Pin);
        break;
    default:
        break;
    }
}
