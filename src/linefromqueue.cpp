#include "linefromqueue.h"

const char *LineFromQueue::tryGetLine(queue_t *queue)
{
    while(!queue_is_empty(queue)) {
        uint8_t character;
        queue_try_remove(queue, &character);
        m_lineExtractor.add(character);
        const char *line = m_lineExtractor.tryGetLine();
        if(line)
            return line;
    }
    return nullptr;
}
