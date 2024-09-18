#ifndef LOGTRANSFORM_H
#define LOGTRANSFORM_H

class LogTransform
{
public:
    LogTransform();
    virtual ~LogTransform();
    void add(char chr);
    bool hasLine() const;
    char* getLine();

private:
    char* m_lineBuffer;
    int m_nextPos = 0;
    bool m_hasCompleteLine = false;
};

#endif // LOGTRANSFORM_H
