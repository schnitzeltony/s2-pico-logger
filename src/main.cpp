#include "led.h"
#include "serialuart.h"
#include "logtransform.h"
#include <stdio.h>

static bool queueToLog(queue_t *queue, LogTransform *log, const char* leadText) {
    bool linePrinted = false;
    while(!queue_is_empty(queue)) {
        uint8_t character;
        queue_try_remove(queue, &character);
        log->add(character);
        const char *line = log->tryGetLine();
        if(line) {
            linePrinted = true;
            printf("%s: %s\r\n",leadText, line);
        }
    }
    return linePrinted;
}

int main() {
    led_init();

    stdio_usb_init();
    constexpr uint8_t LinuxConsoleUartNo = 0;
    constexpr uint8_t SystemCtlUartNo = 1;
    serial_uart_init(LinuxConsoleUartNo, 115200, 1, 0);
    serial_uart_init(SystemCtlUartNo, 9600, 7, 6);

    bool ledOn = true;
    LogTransform *logTransformerSysCtl = new LogTransform;
    queue_t *rx_queueSystemCtl = getRxQueue(SystemCtlUartNo);
    LogTransform *logTransformerLinux = new LogTransform;
    queue_t *rx_queueLinuxConsole = getRxQueue(LinuxConsoleUartNo);

    while (1) {
        bool ledToggle = false;
        if(queueToLog(rx_queueSystemCtl, logTransformerSysCtl, "SystemController"))
            ledToggle = true;
        if(queueToLog(rx_queueLinuxConsole, logTransformerLinux, "Linux"))
            ledToggle = true;
        if(ledToggle) {
            led_switch(ledOn);
            ledOn = !ledOn;
        }
        //tight_loop_contents();
    }
}
