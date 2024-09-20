#ifndef LOGTIMESTAMPGENERATOR_H
#define LOGTIMESTAMPGENERATOR_H

class LogTimeStampGenerator {
public:
    const char* getTimeStampStr() const;
    static const char* getTimeStampBaseFormat();
};

#endif // LOGTIMESTAMPGENERATOR_H