#include "cppmain.hpp"

#include "main.h"
#include "tim.h"
#include "gpio.h"

#include "stm32_led.hpp"

static Stm32Led led_g(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
static Stm32Led led_b(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET);
static Stm32Led led_r(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
static Stm32Led led_o(LED_O_GPIO_Port, LED_O_Pin, GPIO_PIN_SET);

void setup(void) {
    // タイマスタート
	HAL_TIM_Base_Start_IT(&htim6);

    led_o.set_flash_period(10);
    led_r.set_flash_period(2);
    led_g.set_flash_period(1);

    // LEDを点滅させる
    led_b.setOn();
    led_r.setFlash();
    led_o.setFlash();
    led_g.setFlash();
}

void loop(void) {
   if(HAL_GPIO_ReadPin(SW_GPIO_Port, SW_Pin) == GPIO_PIN_SET) {
       led_g.set_flash_period(10);
   }
   else {
       led_g.set_flash_period(1);
   }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if(htim->Instance == TIM6) {
        Stm32Led::interrupt_handler();
    }
}
