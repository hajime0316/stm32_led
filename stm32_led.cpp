/*
 * stm32_led.cpp
 *
 *  Created on: 2019/08/25
 *      Author: shimizu issei
 */

#include"stm32_led.hpp"

#define led_off_pin_state (led_on_pin_state==GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET)

Stm32Led *Stm32Led::last_instance_p = nullptr;

// Definition of public function

Stm32Led::Stm32Led(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin, GPIO_PinState led_on_pin_state) {
    state = LED_OFF;
    led_GPIOx = GPIOx;
    led_GPIO_Pin = GPIO_Pin;

    previous_instance_p = last_instance_p; 
    last_instance_p = this;

    this->led_on_pin_state = led_on_pin_state;
    HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_off_pin_state);
}

Stm32Led::~Stm32Led() {
    if(last_instance_p == nullptr) return;

    if(last_instance_p == this) {
        last_instance_p = this->previous_instance_p;
        return;
    }

    Stm32Led *i_p = last_instance_p;
    while(true) {
        if(i_p->previous_instance_p == this) {
            i_p->previous_instance_p = this->previous_instance_p;
            return;
        }
        else {
            i_p = i_p->previous_instance_p;
            continue;
        }
    }
}

void Stm32Led::setOn(){
    state=LED_ON;
    HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_on_pin_state);
}

void Stm32Led::setOff(){
    state=LED_OFF;
    HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_off_pin_state);
}

void Stm32Led::setFlash(){
    state=LED_FLASH;
}

void Stm32Led::setFlash(unsigned int flash_period){
    set_flash_period(flash_period);
    state=LED_FLASH;
}

void Stm32Led::interrupt_handler() {
    if(last_instance_p == nullptr) return;

    last_instance_p->interrupt_routine();

    return;
}

// Definition of private function

void Stm32Led::set_flash_period(unsigned int flash_period) {
    this->flash_period = flash_period;
}

void Stm32Led::interrupt_routine(){
    switch (state)
    {
    case LED_ON:
        HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_on_pin_state);
        break;
    case LED_OFF:
        HAL_GPIO_WritePin(led_GPIOx,led_GPIO_Pin, led_off_pin_state);
        break;
    case LED_FLASH:
        if(flash_period_count >= flash_period) {
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

    if(previous_instance_p == nullptr) return;

    previous_instance_p->interrupt_routine();
}
