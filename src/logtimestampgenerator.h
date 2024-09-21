#ifndef LOGTIMESTAMPGENERATOR_H
#define LOGTIMESTAMPGENERATOR_H

#include <chrono>

class LogTimeStampGenerator {
public:
    std::chrono::system_clock::time_point getNowSynched() const;
    const char* getTimeStampStr() const;
    static const char* getTimeStampBaseFormat();
    bool setCurrentTime(const char* strCurrentTime);
private:
    std::chrono::system_clock::duration m_currentSetTime;
};

#endif // LOGTIMESTAMPGENERATOR_H