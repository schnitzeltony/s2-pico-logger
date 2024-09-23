#include "timesync.h"
#include "strptime.h"

using namespace std::chrono;

system_clock::time_point TimeSync::getNow() const
{
    return getNowUnadjusted() + m_timeOffset;
}

bool TimeSync::setCurrentTime(const char *timeString)
{
    tm timeStruct = {};
    convertTimeStringToTimeStruct(timeString, timeStruct);
    const auto durationSinceEpoch = getDurationSinceEpoch(timeStruct);
    if(durationSinceEpoch.count() > 0) {
        m_timeOffset = durationSinceEpoch - getNowUnadjusted().time_since_epoch();
        return true;
    }
    return false;
}

const char *TimeSync::getTimeStampSyncFormat()
{
    return "%Y-%m-%d %H:%M:%S";
}

std::chrono::system_clock::time_point TimeSync::getNowUnadjusted() const
{
    return system_clock::now();
}

void TimeSync::convertTimeStringToTimeStruct(const char *timeString, tm &timeStruct)
{
    strptime(timeString, getTimeStampSyncFormat(), &timeStruct);
}

system_clock::duration TimeSync::getDurationSinceEpoch(tm timeStruct)
{
    const time_t timeT = std::mktime(&timeStruct);
    const auto timePoint = system_clock::from_time_t(timeT);
    return timePoint.time_since_epoch();
}
