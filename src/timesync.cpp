#include "timesync.h"
#include "strptime.h"

std::chrono::system_clock::time_point TimeSync::getNowSynched() const
{
    return std::chrono::system_clock::now() + m_currentSetTime;
}

const char *TimeSync::getTimeStampSyncFormat()
{
    return "%Y-%m-%d %H:%M:%S";
}

bool TimeSync::setCurrentTime(const char *strCurrentTime)
{
    tm tm = {};
    strptime(strCurrentTime, getTimeStampSyncFormat(), &tm);
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    std::chrono::system_clock::duration currentSetTime = tp.time_since_epoch();
    if(currentSetTime.count() > 0) {
        m_currentSetTime = currentSetTime;
        return true;
    }
    return false;
}
