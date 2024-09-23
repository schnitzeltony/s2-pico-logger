#include "led.h"
#include "serialuart.h"
#include "linefromqueue.h"
#include "stdintoqueue.h"
#include "logger.h"
#include "commandparser.h"
#include <stdio.h>

StdInToQueue stdioQueueWrapper(256);
constexpr uint8_t LinuxConsoleUartNo = 0;
constexpr uint8_t SystemCtlUartNo = 1;

queue_t *queueStdIn = stdioQueueWrapper.getQueue();
queue_t *queueSystemCtlIn = getRxQueue(SystemCtlUartNo);
queue_t *queueLinuxConsoleIn = getRxQueue(LinuxConsoleUartNo);

LineFromQueue lineFromLinux;
LineFromQueue lineFromSysCtl;
LineFromQueue linesFromCmd;

CommandParser cmdParser;

static bool queueToLog(queue_t *queue, LineFromQueue *queueLine, const char* leadText) {
    bool linePrinted = false;
    const char *line = queueLine->tryGetLine(queue);
    if(line) {
        linePrinted = true;
        Logger::logOutput(leadText, line);
    }
    return linePrinted;
}

int main() {
    led_init();
    led_initialDance();
    cmdParser.addCmd(Command("SETTIME", 1, [&](void* param, std::vector<std::string> cmdParams) {
        (void) param;
        return Logger::setCurrTime(cmdParams.front().data());
    }, nullptr));

    stdio_usb_init();

    serial_uart_init(LinuxConsoleUartNo, 115200, 1, 0);
    serial_uart_init(SystemCtlUartNo, 9600, 5, 4);

    bool ledOn = true;
    while (1) {
        bool ledToggle = false;
        if(queueToLog(queueSystemCtlIn, &lineFromSysCtl, "SystemCtrl"))
            ledToggle = true;
        if(queueToLog(queueLinuxConsoleIn, &lineFromLinux, "LinuxConsole"))
            ledToggle = true;

        const char* cmdLineIn = linesFromCmd.tryGetLine(queueStdIn);
        if(cmdLineIn) {
            ledToggle = true;
            if(!cmdParser.decodeExecuteLine(cmdLineIn))
                Logger::logOutput("Could not process input", cmdLineIn);
        }

        if(ledToggle) {
            led_switch(ledOn);
            ledOn = !ledOn;
        }
        //tight_loop_contents();
    }
}
