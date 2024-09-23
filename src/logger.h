#ifndef LOGGER_H
#define LOGGER_H

#include "timesync.h"

class Logger {
public:
    Logger(TimeSync* syncTime);
    void logOutput(const char* leadText, const char* line);
private:
    TimeSync *m_syncTime;
};

#endif // LOGGER_H
