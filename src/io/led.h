#ifndef LED_H
#define LED_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void led_init(void);
void led_initialDance();
void led_switch(bool on);

#ifdef __cplusplus
}
#endif

#endif // LED_H
