#include "timesync.h"
#include "strptime.h"

using namespace std::chrono;

system_clock::time_point TimeSync::getNow() const
{
    return system_clock::now() + m_currDurationSinceEpoch;
}

bool TimeSync::setCurrentTime(const char *timeString)
{
    tm timeStruct = {};
    convertTimeStringToTimeStruct(timeString, timeStruct);
    const auto durationSinceEpoch = getDurationEpochFromTimeStruct(timeStruct);
    if(durationSinceEpoch.count() > 0) {
        m_currDurationSinceEpoch = durationSinceEpoch;
        return true;
    }
    return false;
}

const char *TimeSync::getTimeStampSyncFormat()
{
    return "%Y-%m-%d %H:%M:%S";
}

void TimeSync::convertTimeStringToTimeStruct(const char *timeString, tm &timeStruct)
{
    strptime(timeString, getTimeStampSyncFormat(), &timeStruct);
}

system_clock::duration TimeSync::getDurationEpochFromTimeStruct(const tm &timeStruct)
{
    const time_t timeT = std::mktime(const_cast<tm *>(&timeStruct)); // std::mktime no const argument
    const auto timePoint = system_clock::from_time_t(timeT);
    return timePoint.time_since_epoch();
}
