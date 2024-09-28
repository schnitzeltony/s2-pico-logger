#include "stdintoqueue.h"
#include <pico/stdio.h>

StdInToQueue::StdInToQueue(int queueSize) {
    queue_init(&m_queue, 1, queueSize);
}

queue_t* StdInToQueue::getQueue() {
    return &m_queue;
}

void StdInToQueue::enableAfterStdInInit()
{
    stdio_set_chars_available_callback(StdInToQueue::handleInput, &m_queue);
}

void StdInToQueue::handleInput(void *param) {
    int charGetWide;
    while((charGetWide = getchar_timeout_us(0)) != PICO_ERROR_TIMEOUT) {
        queue_t *queue = static_cast <queue_t*>(param);
        uint8_t character = static_cast <uint8_t>(charGetWide);
        queue_try_add(queue, &character);
    }
}
