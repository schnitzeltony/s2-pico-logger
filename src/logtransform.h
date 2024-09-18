#ifndef LOGTRANSFORM_H
#define LOGTRANSFORM_H

class LogTransform
{
public:
    LogTransform();
    virtual ~LogTransform();
    void add(char chr);
    const char* tryGetLine();

private:
    char* m_lineBuffer;
    int m_currPos = 0;
    bool m_hasCompleteLine = false;
};

#endif // LOGTRANSFORM_H
