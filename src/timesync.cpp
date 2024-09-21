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
    system_clock::duration durationSinceEpoch = getDurationEpochFromTimeStruct(timeStruct);
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
    const auto timePoint = system_clock::from_time_t(std::mktime(const_cast<tm *>(&timeStruct))); // std::mktime no const argument
    return timePoint.time_since_epoch();
}
