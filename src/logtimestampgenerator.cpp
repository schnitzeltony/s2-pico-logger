#include "logtimestampgenerator.h"
#include "strptime.h"
#include <stdio.h>

static char timeStrSeconds[sizeof("1970-01-01 00:00:0")+1];
static char timeStrMs[sizeof("000")+1];
static char timeStrTotal[sizeof(timeStrSeconds)+ sizeof(timeStrMs)];

const char* LogTimeStampGenerator::getTimeStampStr() const
{
    const auto nowSynched = getNowSynched();
    time_t timeT = std::chrono::system_clock::to_time_t(nowSynched);
    const struct tm *lTime = localtime(&timeT);
    strftime(timeStrSeconds, 256, getTimeStampBaseFormat(), lTime);
    const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(nowSynched.time_since_epoch()) % 1000;
    sprintf(timeStrMs, "%03d", nowMs.count());
    sprintf(timeStrTotal, "%s.%s", timeStrSeconds, timeStrMs);
    return timeStrTotal;
}

std::chrono::system_clock::time_point LogTimeStampGenerator::getNowSynched() const
{
    return std::chrono::system_clock::now() + m_currentSetTime;
}

const char *LogTimeStampGenerator::getTimeStampBaseFormat()
{
    return "%Y-%m-%d %H:%M:%S";
}

bool LogTimeStampGenerator::setCurrentTime(const char *strCurrentTime)
{
    tm tm = {};
    strptime(strCurrentTime, getTimeStampBaseFormat(), &tm);
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    std::chrono::system_clock::duration currentSetTime = tp.time_since_epoch();
    if(currentSetTime.count() > 0) {
        m_currentSetTime = currentSetTime;
        return true;
    }
    return false;
}
