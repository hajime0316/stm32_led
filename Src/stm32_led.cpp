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

int Led::setOn(){
    state=1;
}
int Led::setOff(){
    state=0;
}
int Led::setFlash(){
    state=2;
}

void Led::interrut_toutine(){
    switch (state)
    {
    case 1:
        HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, SET);
        break;
    case 0:
        HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, RESET);
        break;
    case 2:
        HAL_GPIO_TogglePin(led_GPIOx,led_GPIO_Pin);
        break;
    default:
        break;
    }
}
