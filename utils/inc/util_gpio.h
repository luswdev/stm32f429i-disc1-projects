/**
 * @file    util_gpio.h
 * @brief   stm32f4xx gpio function define
 *
 * @author  LuSkywalker <callumlu@gmail.com>
 * @note    Copyright (c) 2023, LuSkywalker
 */

#ifndef __UTIL_GPIO_H__
#define __UTIL_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#undef EXT
#ifdef UTIL_GPIO_SET
#define EXT
#else
#define EXT extern
#endif

#include <stm32f4xx.h>

typedef struct gpio_s {
    GPIO_TypeDef*   port;
    uint16_t        pin;
    uint32_t        rcc_clock;
    uint8_t         source;
} gpio_t;

EXT gpio_t util_gpio_get_by_name(const char gpio_name[]);
EXT void util_gpio_toggle(gpio_t gpio);
EXT void util_gpio_on(gpio_t gpio);
EXT void util_gpio_off(gpio_t gpio);

#ifdef __cplusplus
}
#endif

#endif /* __UTIL_GPIO_H__ */
