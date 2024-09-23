#include "led.h"
#include "serialuart.h"
#include "linefromqueue.h"
#include "stdintoqueue.h"
#include "logger.h"
#include "commandparser.h"
#include <stdio.h>

TimeSync systemTime;
Logger logger(&systemTime);

static StdInToQueue stdioQueueWrapper(256);
static constexpr uint8_t LinuxConsoleUartNo = 0;
static constexpr uint8_t SystemCtlUartNo = 1;

static queue_t *queueStdIn = stdioQueueWrapper.getQueue();
static queue_t *queueSystemCtlIn = getRxQueue(SystemCtlUartNo);
static queue_t *queueLinuxConsoleIn = getRxQueue(LinuxConsoleUartNo);

static LineFromQueue linesFromCmd(queueStdIn);
static LineFromQueue lineFromSysCtl(queueSystemCtlIn);
static LineFromQueue lineFromLinux(queueLinuxConsoleIn);

static CommandParser cmdParser;

static bool queueToLog(LineFromQueue *queueLine, const char* leadText) {
    bool linePrinted = false;
    const char *line = queueLine->tryGetLine();
    if(line) {
        linePrinted = true;
        logger.logOutput(leadText, line);
    }
    return linePrinted;
}

int main() {
    led_init();
    led_initialDance();
    cmdParser.addCmd(Command("SETTIME", 1, [&](void* param, std::vector<std::string> cmdParams) {
        return systemTime.setCurrentTime(cmdParams.front().data());
    },
    nullptr));

    stdio_usb_init();
    serial_uart_init(LinuxConsoleUartNo, 115200, 1, 0);
    serial_uart_init(SystemCtlUartNo, 9600, 5, 4);

    bool ledOn = true;
    while (1) {
        bool ledToggle = false;
        if(queueToLog(&lineFromSysCtl, "SystemCtrl"))
            ledToggle = true;
        if(queueToLog(&lineFromLinux, "LinuxConsole"))
            ledToggle = true;

        const char* cmdLineIn = linesFromCmd.tryGetLine();
        if(cmdLineIn) {
            ledToggle = true;
            if(!cmdParser.decodeExecuteLine(cmdLineIn))
                logger.logOutput("Could not process input", cmdLineIn);
        }

        if(ledToggle) {
            led_switch(ledOn);
            ledOn = !ledOn;
        }
        //tight_loop_contents();
    }
}
