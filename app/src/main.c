/**
 * @file    main.c
 * @brief   main entry point declare
 *
 * @author  LuSkywalker <callumlu@gmail.com>
 * @note    Copyright (c) 2023, LuSkywalker
 */

#include <stdint.h>

#include "util_clk.h"
#include "usr_led.h"
#include "usr_btn.h"
#include "usr_console.h"

#define MAIN_SET
#include "main.h"

#define PWM_FREQ    1000

static led_spd_t preLedSpd;

/**
 * @brief main program
 */
int main(void)
{
    util_clock_init();

    usr_console_init();

    usr_led_init(LED3);
    usr_led_init(LED4);
    usr_led_init(USR_LED);

    usr_btn_init(BTN_USER);

    // usr_led_on(LED3);
    // usr_led_off(LED4);

    DBG_MSG("press button to change led pulse speed...\r\n");
    for ( ; ; ) {
        led_spd_t curLedSpd = (usr_led_get_spd() * 2 + 1) * 10;
        int32_t pulseSec = (DUTY_BASE / curLedSpd) * PWM_CONTINUE_MS;
        if (preLedSpd != curLedSpd) {
            DBG_MSG("pulse per %d ms...\r\n", (int)pulseSec);
        }

        for (int i = 0; i <= DUTY_BASE; i += curLedSpd * 2) {
            usr_led_pwm(USR_LED, PWM_FREQ, i);
            //usr_led_pwm(LED4, PWM_FREQ, i);
        }

        /* still for full scale */
        usr_led_on(USR_LED);
        util_delay_ms(pulseSec / 4);

        for (int i = DUTY_BASE; i >= 0; i -= curLedSpd) {
            usr_led_pwm(USR_LED, PWM_FREQ, i);
            //usr_led_pwm(LED4, PWM_FREQ, i);
        }

        /* still for empty scale */
        usr_led_off(USR_LED);
        util_delay_ms(pulseSec / 5);

        preLedSpd = curLedSpd;
    }
}
