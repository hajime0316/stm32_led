/*
 * stm32_led.hpp
 *
 *  Created on: 2019/08/25
 *      Author: shimizu issei
 */

#ifndef STM32_LED_HPP_
#define STM32_LED_HPP_
#include "main.h"

class Stm32Led {
private:
    enum {
        LED_ON,
        LED_OFF,
        LED_FLASH
    } state;
    GPIO_TypeDef* led_GPIOx;
    uint16_t led_GPIO_Pin;
    GPIO_PinState led_on_pin_state = GPIO_PIN_SET;
    unsigned int flash_period = 0;
    unsigned int flash_period_count = 0;
    void set_flash_period(unsigned int flash_period);
public:
    Stm32Led(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin, GPIO_PinState led_on_pin_state);
    ~Stm32Led();
    void setOn();
    void setOff();
    void setFlash();
    void setFlash(unsigned int flash_period);

    // LEDモジュールの割り込みハンドラ
    // TIM割り込み関数の中でコール
    static void interrupt_handler();

private:
    // 全インスタンスにアクセスするためのポインタ．
    // 割り込みルーチンの中で使う．
    Stm32Led        *previous_instance_p;    // 自身の前に生成されたインスタンスへのポインタ
                                        // 前のインスタンスがない場合はnull
    static Stm32Led *last_instance_p;        // 最後に生成したインスタンスへのポインタ

    // interrupt_handler関数から呼び出される関数
    void interrupt_routine();
};

#endif /* STM32_LED_HPP_ */
