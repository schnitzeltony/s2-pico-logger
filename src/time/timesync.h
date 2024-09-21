#ifndef TIMESYNC_H
#define TIMESYNC_H

#include <chrono>

class TimeSync {
public:
    std::chrono::system_clock::time_point getNow() const;
    bool setCurrentTime(const char* timeString);
private:
    static const char* getTimeStampSyncFormat();
    static void convertTimeStringToTimeStruct(const char *timeString, tm &timeStruct);
    static std::chrono::system_clock::duration getDurationSinceEpoch(const tm &timeStruct);
    std::chrono::system_clock::duration m_currDurationSinceEpoch;
};

#endif // TIMESYNC_H