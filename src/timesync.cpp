#include "timesync.h"
#include "strptime.h"

std::chrono::system_clock::time_point TimeSync::getNow() const
{
    return std::chrono::system_clock::now() + m_currDurationSinceEpoch;
}

bool TimeSync::setCurrentTime(const char *strTimeStamp)
{
    tm timeStruct = {};
    strptime(strTimeStamp, getTimeStampSyncFormat(), &timeStruct);
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&timeStruct));
    std::chrono::system_clock::duration durationSinceEpoch = timePoint.time_since_epoch();
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
