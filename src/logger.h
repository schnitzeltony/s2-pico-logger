#ifndef LOGGER_H
#define LOGGER_H

#include "timesync.h"

class Logger {
public:
    static void logOutput(const char* leadText, const char* line);
    static bool setCurrTime(const char* timeString);
private:
    static Logger* getInstance();
    static Logger* m_instance;
    TimeSync m_syncTime;
};

#endif // LOGGER_H
