#ifndef STDINTOQUEUE_H
#define STDINTOQUEUE_H

#include "pico/stdlib.h"
#include "pico/util/queue.h"

class StdInToQueue
{
public:
    static StdInToQueue* getInstance(); // not thread safe!
    queue_t* getQueue();
    
private:
    StdInToQueue(int queueSize);
    static void handleInput(void *param);
    queue_t m_queue;
    static StdInToQueue* m_instance;
};

#endif // STDINTOQUEUE_H