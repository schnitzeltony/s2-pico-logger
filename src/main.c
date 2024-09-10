#include "led.h"
#include "serialuart.h"

int main() {
    led_init();
    serial_uart_init(0, 9600, 1, 0);

    led_switch(true);

    while (1) {
        queue_t *rx_queue = getRxQueue(0);
        queue_t *tx_queue = getTxQueue(0);
        bool starRequired = false;
        while(!queue_is_empty(rx_queue)) {
            starRequired = true;
            uint8_t character;
            queue_try_remove(rx_queue, &character);
            queue_try_add(tx_queue, &character);
        }
        if(starRequired)
            startTransmitAfterAddingTransmitData(0);
        //tight_loop_contents();
    }
}
