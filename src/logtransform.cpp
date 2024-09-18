#include "logtransform.h"
#include <pico/assert.h>

constexpr int MaxLineLen = 255;

LogTransform::LogTransform()
{
    m_lineBuffer = new char[MaxLineLen+1];
}

LogTransform::~LogTransform()
{
    delete[] m_lineBuffer;
}

void LogTransform::add(char chr)
{
    if(chr == 0 || chr == 255)
        return;
    if(m_hasCompleteLine)
        return;
    if(m_currPos >= MaxLineLen) {
        m_hasCompleteLine = true;
        return;
    }
    if(chr == '\r') {
        m_hasCompleteLine = true;
        return;
    }
    m_lineBuffer[m_currPos++] = chr;
}

bool LogTransform::hasLine() const
{
    return m_hasCompleteLine;
}

char* LogTransform::getLine()
{
    assert(m_hasCompleteLine);
    m_hasCompleteLine = false;
    m_lineBuffer[m_currPos] = 0;
    m_currPos = 0;
    return m_lineBuffer;
}