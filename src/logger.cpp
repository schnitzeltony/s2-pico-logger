#include "logger.h"
#include "timestringgenerator.h"
#include <stdio.h>

Logger::Logger(TimeSync *syncTime) :
    m_syncTime(syncTime)
{
}

void Logger::logOutput(const char *leadText, const char *line)
{
    printf("%s %s: '%s'\r\n", TimeStringGenerator::getTimeStampStr(m_syncTime->getNow()), leadText, line);
}
