#ifndef LOGTIMESTAMPGENERATOR_H
#define LOGTIMESTAMPGENERATOR_H

#include <chrono>

class LogTimeStampGenerator {
public:
    static const char* getTimeStampStr(const std::chrono::system_clock::time_point &time);
private:
    static const char* getTimeStampBaseFormat();
    static const struct tm* getLocalImeStruct(const std::chrono::system_clock::time_point &time);
};

#endif // LOGTIMESTAMPGENERATOR_H