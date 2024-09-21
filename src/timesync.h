#ifndef TIMESYNC_H
#define TIMESYNC_H

#include <chrono>

class TimeSync {
public:
    std::chrono::system_clock::time_point getNow() const;
    bool setCurrentTime(const char* strTimeStamp);
private:
    static const char* getTimeStampSyncFormat();
    static void convertTimeStampToTime(const char* timeStamp, tm &timeStruct);
    std::chrono::system_clock::duration m_currDurationSinceEpoch;
};

#endif // TIMESYNC_H