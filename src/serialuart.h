#ifndef SERIALUART_H
#define SERIALUART_H

#include "pico/stdlib.h"

void serial_uart_init(uint8_t uartNo, uint32_t baudrate, uint8_t rxPin, uint8_t txPin);
void serial_uart_enable_rx_interrupt(uint8_t uartNo);

#endif // SERIALUART_H
