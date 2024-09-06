#include "led.h"
#include "seriallinuxconsole.h"

int main() {
    led_init();
    serial_linux_init();

    led_switch(true);

    while (1)
        tight_loop_contents();
}
