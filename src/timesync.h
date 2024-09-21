#ifndef TIMESYNC_H
#define TIMESYNC_H

#include <chrono>

class TimeSync {
public:
    std::chrono::system_clock::time_point getNowSynched() const;
    bool setCurrentTime(const char* strCurrentTime);
private:
    static const char* getTimeStampSyncFormat();
    std::chrono::system_clock::duration m_currentSetTime;
};

#endif // TIMESYNC_H