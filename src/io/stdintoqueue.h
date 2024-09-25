#ifndef STDINTOQUEUE_H
#define STDINTOQUEUE_H

#include <pico/util/queue.h>

class StdInToQueue
{
public:
    StdInToQueue(int queueSize);
    queue_t* getQueue();
    void enableAfterStdInInit();
    
private:
    static void handleInput(void *param);
    queue_t m_queue;
    static StdInToQueue* m_instance;
};

#endif // STDINTOQUEUE_H