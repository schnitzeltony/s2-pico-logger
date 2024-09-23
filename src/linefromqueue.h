#ifndef LINEFROMQUEUE_H
#define LINEFROMQUEUE_H

#include "lineextractor.h"
#include <pico/util/queue.h>

class LineFromQueue
{
public:
    const char* tryGetLine(queue_t *queue);

private:
    LineExtractor m_lineExtractor;
};

#endif // LINEFROMQUEUE_H
