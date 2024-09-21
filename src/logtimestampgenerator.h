#ifndef LOGTIMESTAMPGENERATOR_H
#define LOGTIMESTAMPGENERATOR_H

#include <chrono>

class LogTimeStampGenerator {
public:
    static const char* getTimeStampStr(std::chrono::system_clock::time_point time);
private:
    static const char* getTimeStampBaseFormat();
};

#endif // LOGTIMESTAMPGENERATOR_H