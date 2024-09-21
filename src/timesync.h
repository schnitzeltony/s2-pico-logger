#ifndef TIMESYNC_H
#define TIMESYNC_H

#include <chrono>

class TimeSync {
public:
    std::chrono::system_clock::time_point getNowSynched() const;
    static const char* getTimeStampSyncFormat();
    bool setCurrentTime(const char* strCurrentTime);
private:
    std::chrono::system_clock::duration m_currentSetTime;
};

#endif // TIMESYNC_H