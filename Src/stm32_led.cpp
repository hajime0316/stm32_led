/*
 * stm32_led.cpp
 *
 *  Created on: 2019/08/25
 *      Author: shimizu issei
 */

#include"stm32_led.hpp"

#define led_off_pin_state (led_on_pin_state==GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET)

Led::Led(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin) {
    state = LED_OFF;
    led_GPIOx = GPIOx;
    led_GPIO_Pin = GPIO_Pin;

    HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_off_pin_state);
}
Led::Led(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin, GPIO_PinState led_on_pin_state) {
    state = LED_OFF;
    led_GPIOx = GPIOx;
    led_GPIO_Pin = GPIO_Pin;

    this->led_on_pin_state = led_on_pin_state;
    HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_off_pin_state);
}

void Led::setOn(){
    state=LED_ON;
    HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_on_pin_state);
}
void Led::setOff(){
    state=LED_OFF;
    HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_off_pin_state);
}
void Led::setFlash(){
    state=LED_FLASH;
}

void Led::interrut_toutine(){
    switch (state)
    {
    case LED_ON:
        HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_on_pin_state);
        break;
    case LED_OFF:
        HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_off_pin_state);
        break;
    case LED_FLASH:
        static unsigned int flash_period_count = 0;

        if(flash_period_count == flash_period) {
            HAL_GPIO_TogglePin(led_GPIOx,led_GPIO_Pin);
            flash_period_count = 0;
        }
        else {
            flash_period_count++;
        }
        
        break;
    default:
        break;
    }
}

void Led::set_flash_period(unsigned int flash_period) {
    this->flash_period = flash_period;
}
