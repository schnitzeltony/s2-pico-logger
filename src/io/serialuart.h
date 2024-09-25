#ifndef SERIALUART_H
#define SERIALUART_H

#include <pico/util/queue.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void serial_uart_init(uint8_t uartNo, uint32_t baudrate, uint8_t rxPin, uint8_t txPin);
queue_t *getRxQueue(uint8_t uartNo);
queue_t *getTxQueue(uint8_t uartNo);
void startTransmitAfterAddingTransmitData(uint8_t uartNo);

#ifdef __cplusplus
}
#endif

#endif // SERIALUART_H
