#include "led.h"
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

#if defined(PICO_DEFAULT_LED_PIN)
void led_init(void)
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
}

void led_switch(bool on)
{
    gpio_put(PICO_DEFAULT_LED_PIN, on);
}

#elif defined(CYW43_WL_GPIO_LED_PIN) // Pico W
void led_init(void)
{
    cyw43_arch_init();
}

void led_switch(bool on)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
}}
#endif


