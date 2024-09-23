#include "linefromqueue.h"

LineFromQueue::LineFromQueue(queue_t *queue) :
    m_queue(queue)
{
}

const char *LineFromQueue::tryGetLine()
{
    while(!queue_is_empty(m_queue)) {
        uint8_t character;
        queue_try_remove(m_queue, &character);
        m_lineExtractor.add(character);
        const char *line = m_lineExtractor.tryGetLine();
        if(line)
            return line;
    }
    return nullptr;
}
