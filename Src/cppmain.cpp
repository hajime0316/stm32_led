#include "cppmain.hpp"

#include "main.h"
#include "tim.h"
#include "gpio.h"

#include "stm32_led.hpp"

void setup(void) {
    static Led led(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim6);
    led.setFlash();
}

void loop(void) {
   
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if(htim->Instance == TIM6) {
        Led::interrupt_handler();
    }
}
