#include "cppmain.hpp"

#include "main.h"
#include "tim.h"
#include "gpio.h"

#include "stm32_led.hpp"

Led led(GPIOD,GPIO_PIN_14);

void setup(void) {
	HAL_TIM_Base_Start_IT(&htim6);
    led.setFlash();
}

void loop(void) {
   
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if(htim->Instance == TIM6) {
        led.interrut_toutine();
    }
}
