#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

void led_init(void);
void led_switch(bool on);

#ifdef __cplusplus
}
#endif

#endif // LED_H
