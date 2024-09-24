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
}

#else
void led_init(void) {}
void led_switch(bool on) {
    (void)on;
}
#endif

void led_initialDance() {
    const uint32_t msWait = 100;
    for(int i=0; i<3; i++) {
        led_switch(true);
        sleep_ms(msWait);
        led_switch(false);
        sleep_ms(msWait);
    }
}

