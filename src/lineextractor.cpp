#include "lineextractor.h"
#include <pico/assert.h>

void LineExtractor::add(char chr)
{
    if(chr == 0x00 || chr == 0xFF || chr == '\n')
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

const char* LineExtractor::tryGetLine()
{
    if(!m_hasCompleteLine)
        return nullptr;
    m_hasCompleteLine = false;
    m_lineBuffer[m_currPos] = 0;
    m_currPos = 0;
    return m_lineBuffer;
}