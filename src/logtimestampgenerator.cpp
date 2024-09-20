#include "logtimestampgenerator.h"
#include <stdio.h>
#include <chrono>

static char timeStrSeconds[sizeof("1970-01-01 00:00:0")+1];
static char timeStrMs[sizeof("000")+1];
static char timeStrTotal[sizeof(timeStrSeconds)+ sizeof(timeStrMs)];

const char* LogTimeStampGenerator::getTimeStampStr() const
{
    const auto now = std::chrono::system_clock::now();
    time_t nowTimeT = std::chrono::system_clock::to_time_t(now);
    const struct tm *lTime = localtime(&nowTimeT);
    strftime(timeStrSeconds, 256, getTimeStampBaseFormat(), lTime);
    const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    sprintf(timeStrMs, "%03d", nowMs.count());
    sprintf(timeStrTotal, "%s.%s", timeStrSeconds, timeStrMs);
    return timeStrTotal;
}

const char *LogTimeStampGenerator::getTimeStampBaseFormat()
{
    return "%Y-%m-%d %H:%M:%S";
}
