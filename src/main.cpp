#include "led.h"
#include "serialuart.h"
#include "logtransform.h"
#include "filesystem/vfs.h"
#include <stdio.h>

int main() {
    led_init();
    serial_uart_init(0, 9600, 1, 0);

    fs_init();
    FILE *fp = fopen("HELLO.TXT", "w");
    fprintf(fp, "Hello World!\n");
    fclose(fp);

    bool ledOn = false;
    LogTransform logTransformer; // for now just cpp test
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
        if(starRequired) {
            startTransmitAfterAddingTransmitData(0);
            led_switch(ledOn);
            ledOn = !ledOn;
        }
        //tight_loop_contents();
    }
}
