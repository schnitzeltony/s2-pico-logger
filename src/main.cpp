#include "led.h"
#include "serialuart.h"
#include "lineextractor.h"
#include "stdintoqueue.h"
#include "timestringgenerator.h"
#include "timesync.h"
#include "commandparser.h"
#include <stdio.h>

TimeSync timeSync;
CommandParser cmdParser;

static const char* tryGetLine(queue_t *queue, LineExtractor *log) {
    while(!queue_is_empty(queue)) {
        uint8_t character;
        queue_try_remove(queue, &character);
        log->add(character);
        const char *line = log->tryGetLine();
        if(line)
            return line;
    }
    return nullptr;
}

static void logOutput(const char* leadText, const char* line) {
    std::chrono::system_clock::time_point nowSynced = timeSync.getNow();
    printf("%s %s: %s\r\n", TimeStringGenerator::getTimeStampStr(nowSynced), leadText, line);
}

static bool queueToLog(queue_t *queue, LineExtractor *log, const char* leadText) {
    bool linePrinted = false;
    const char *line = tryGetLine(queue, log);
    if(line) {
        linePrinted = true;
        logOutput(leadText, line);
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
    cmdParser.addCmd(Command("SYNC", 1, nullptr, nullptr));

    timeSync.setCurrentTime("2024-09-21 14:00:30");

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
        if(queueToLog(queueSystemCtlIn, lineExtractSysCtl, "SystemCtrl"))
            ledToggle = true;
        if(queueToLog(queueLinuxConsoleIn, lineExtractLinux, "LinuxConsole"))
            ledToggle = true;

        const char* cmdLineIn = tryGetLine(queueStdIn, lineExtractStdIn);
        if(cmdLineIn) {
            ledToggle = true;
            if(!cmdParser.decodeExecuteLine(cmdLineIn))
                logOutput("Command failed", cmdLineIn);
        }

        if(ledToggle) {
            led_switch(ledOn);
            ledOn = !ledOn;
        }
        //tight_loop_contents();
    }
}
