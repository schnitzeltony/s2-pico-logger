#include "timestringgenerator.h"
#include <stdio.h>

static char timeStrSeconds[sizeof("1970-01-01 00:00:00")+1];
static char timeStrMs[sizeof("000")+1];
static char timeStrTotal[sizeof(timeStrSeconds)+ sizeof(timeStrMs)];

const char *TimeStringGenerator::getTimeStampStr(const std::chrono::system_clock::time_point &time)
{
    const struct tm *lTime = getLocalTimeStruct(time);
    const auto nowMs = getMsPart(time);
    strftime(timeStrSeconds, sizeof(timeStrSeconds), getTimeStampBaseFormat(), lTime);
    sprintf(timeStrMs, "%03d", nowMs.count());
    sprintf(timeStrTotal, "%s.%s", timeStrSeconds, timeStrMs);
    return timeStrTotal;
}

const char *TimeStringGenerator::getTimeStampBaseFormat()
{
    return "%Y-%m-%d %H:%M:%S";
}

const tm *TimeStringGenerator::getLocalTimeStruct(const std::chrono::system_clock::time_point &time)
{
    const time_t timeT = std::chrono::system_clock::to_time_t(time);
    return localtime(&timeT); // man localtime: static => no delete / not thread safe
}

const std::chrono::milliseconds TimeStringGenerator::getMsPart(const std::chrono::system_clock::time_point &time)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()) % 1000;
}
