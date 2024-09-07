#include "led.h"
#include "serialuart.h"

int main() {
    led_init();
    serial_uart_init(0, 9600, 1, 0);
    serial_uart_enable_interrupt(0);

    led_switch(true);

    while (1) {
        tight_loop_contents();
    }
}
