/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include <stdio.h>

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

#define DOT_DELAY_MS 200
#define DASH_DELAY_MS 600
#define GBWORD_DELAY_MS 1400


// Perform initialisation
int pico_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
#endif
}

// Turn the led on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

void dot()
{
    pico_set_led(true);
    sleep_ms(DOT_DELAY_MS);
    pico_set_led(false);
}

void dash()
{
    pico_set_led(true);
    sleep_ms(DASH_DELAY_MS);
    pico_set_led(false);
}

int main() {
    stdio_init_all();
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);
    while (true) {
        //H d d d d
        for(int i=0;i<4;i++)
        {
            dot();
            sleep_ms(DOT_DELAY_MS);
        }
        sleep_ms(DOT_DELAY_MS);
        sleep_ms(DOT_DELAY_MS);
        //E d
        dot();
        sleep_ms(DASH_DELAY_MS);
        //L d - d d
        dot();
        sleep_ms(DOT_DELAY_MS);
        dash();
        sleep_ms(DOT_DELAY_MS);
        dot();
        sleep_ms(DOT_DELAY_MS);
        dot();
        sleep_ms(DASH_DELAY_MS);
        //P . - - .
        dot();
        sleep_ms(DOT_DELAY_MS);
        dash();
        sleep_ms(DOT_DELAY_MS);
        dash();
        sleep_ms(DOT_DELAY_MS);
        dot();
        sleep_ms(DASH_DELAY_MS);
        //! -.-.--
        dash();
        sleep_ms(DOT_DELAY_MS);
        dot();
        sleep_ms(DOT_DELAY_MS);
        dash();
        sleep_ms(DOT_DELAY_MS);
        dot();
        sleep_ms(DOT_DELAY_MS);
        dash();
        sleep_ms(DOT_DELAY_MS);
        dash();
        sleep_ms(GBWORD_DELAY_MS);
        printf("Hello\n");
    }
}
