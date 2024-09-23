#ifndef LINEEXTRACTOR_H
#define LINEEXTRACTOR_H

class LineExtractor
{
public:
    LineExtractor();
    virtual ~LineExtractor();
    void add(char chr);
    const char* tryGetLine();

private:
    char* m_lineBuffer;
    int m_currPos = 0;
    bool m_hasCompleteLine = false;
};

#endif // LINEEXTRACTOR_H
