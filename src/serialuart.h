#ifndef SERIALUART_H
#define SERIALUART_H

#include "pico/stdlib.h"
#include "pico/util/queue.h"

void serial_uart_init(uint8_t uartNo, uint32_t baudrate, uint8_t rxPin, uint8_t txPin);
void serial_uart_enable_interrupt(uint8_t uartNo);
queue_t *getRxQueue(uint8_t uartNo);
queue_t *getTxQueue(uint8_t uartNo);

#endif // SERIALUART_H
