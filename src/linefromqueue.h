#ifndef LINEFROMQUEUE_H
#define LINEFROMQUEUE_H

#include "lineextractor.h"
#include <pico/util/queue.h>

class LineFromQueue
{
public:
    LineFromQueue(queue_t *queue);
    const char* tryGetLine();

private:
    LineExtractor m_lineExtractor;
    queue_t *m_queue;
};

#endif // LINEFROMQUEUE_H
