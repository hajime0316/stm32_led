#include "cppmain.hpp"

#include "main.h"
#include "tim.h"
#include "gpio.h"

#include "stm32_led.hpp"

void setup(void) {

}

void loop(void) {

}

void HAL_TIM_PeriodElapsedCallback(TIM_HanleTypeDef *htim) {
    if(htim->Instance == TIM6) {

    }
}