#include "logger.h"
#include "timestringgenerator.h"
#include <stdio.h>

Logger* Logger::m_instance = nullptr;

void Logger::logOutput(const char *leadText, const char *line)
{
    std::chrono::system_clock::time_point nowSynced = getInstance()->m_syncTime.getNow();
    printf("%s %s: '%s'\r\n", TimeStringGenerator::getTimeStampStr(nowSynced), leadText, line);
}

bool Logger::setCurrTime(const char *timeString)
{
    return getInstance()->m_syncTime.setCurrentTime(timeString);
}

Logger *Logger::getInstance()
{
    if(!m_instance)
        m_instance = new Logger;
    return m_instance;
}
