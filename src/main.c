#include "led.h"
#include "seriallinuxconsole.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

int main() {
    led_init();
    serial_linux_init();

    led_switch(true);

    while (1)
        tight_loop_contents();
}

/// \end:uart_advanced[]
