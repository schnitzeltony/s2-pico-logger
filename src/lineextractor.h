#ifndef LINEEXTRACTOR_H
#define LINEEXTRACTOR_H

class LineExtractor
{
public:
    void add(char chr);
    const char* tryGetLine();

private:
    static constexpr int MaxLineLen = 255;
    char m_lineBuffer[MaxLineLen+1];
    int m_currPos = 0;
    bool m_hasCompleteLine = false;
};

#endif // LINEEXTRACTOR_H
