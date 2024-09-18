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
    if(m_hasCompleteLine)
        return;
    if(chr == '\r')
        return;
    if(m_nextPos > MaxLineLen) {
        m_hasCompleteLine = true;
        return;
    }
    if(chr == '\n') {
        m_hasCompleteLine = true;
        return;
    }
    m_lineBuffer[m_nextPos] = chr;
    m_nextPos++;
}

bool LogTransform::hasLine() const
{
    return m_hasCompleteLine;
}

char* LogTransform::getLine()
{
    assert(m_hasCompleteLine);
    m_lineBuffer[m_nextPos] = 0;
    m_hasCompleteLine = false;
    return m_lineBuffer;
}