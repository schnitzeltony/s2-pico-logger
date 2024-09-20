#include "led.h"
#include "serialuart.h"
#include "lineextractor.h"
#include "stdintoqueue.h"
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

static void initialLEDDance() {
    constexpr uint32_t msWait = 100;
    for(int i=0; i<3; i++) {
        led_switch(true);
        sleep_ms(msWait);
        led_switch(false);
        sleep_ms(msWait);
    }
}

int main() {
    led_init();
    initialLEDDance();

    constexpr uint8_t LinuxConsoleUartNo = 0;
    constexpr uint8_t SystemCtlUartNo = 1;
    LineExtractor *lineExtractSysCtl = new LineExtractor;
    queue_t *queueSystemCtlIn = getRxQueue(SystemCtlUartNo);
    LineExtractor *lineExtractLinux = new LineExtractor;
    queue_t *queueLinuxConsoleIn = getRxQueue(LinuxConsoleUartNo);

    stdio_usb_init();
    LineExtractor *lineExtractStdIn = new LineExtractor;
    queue_t *queueStdIn = StdInToQueue::getInstance()->getQueue();

    serial_uart_init(LinuxConsoleUartNo, 115200, 1, 0);
    serial_uart_init(SystemCtlUartNo, 9600, 5, 4);

    bool ledOn = true;
    while (1) {
        bool ledToggle = false;
        if(queueToLog(queueSystemCtlIn, lineExtractSysCtl, "SystemController"))
            ledToggle = true;
        if(queueToLog(queueLinuxConsoleIn, lineExtractLinux, "Linux"))
            ledToggle = true;
        if(queueToLog(queueStdIn, lineExtractStdIn, "StdIn"))
            ledToggle = true;
        if(ledToggle) {
            led_switch(ledOn);
            ledOn = !ledOn;
        }
        //tight_loop_contents();
    }
}
