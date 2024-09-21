#ifndef TimeStringGenerator_H
#define TimeStringGenerator_H

#include <chrono>

class TimeStringGenerator {
public:
    static const char* getTimeStampStr(const std::chrono::system_clock::time_point &time);
private:
    static const char* getTimeStampBaseFormat();
    static const tm* getLocalTimeStruct(const std::chrono::system_clock::time_point &time);
    static const std::chrono::milliseconds getMsPart(const std::chrono::system_clock::time_point &time);
};

#endif // TimeStringGenerator_H