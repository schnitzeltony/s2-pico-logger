#include "serialuart.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

static void uart_rx_interrupt0()
{
}

static void uart_rx_interrupt1()
{
}

void serial_uart_init(uint8_t uartNo, uint32_t baudrate, uint8_t rxPin, uint8_t txPin)
{
    uart_inst_t *uart = uart_get_instance(uartNo);
    uart_init(uart, baudrate);

    gpio_set_function(txPin, UART_FUNCSEL_NUM(uart, txPin));
    gpio_set_function(rxPin, UART_FUNCSEL_NUM(uart, rxPin));

    uart_set_hw_flow(uart, false, false);
    uart_set_format(uart, 8, 1, UART_PARITY_NONE);
}

void serial_uart_enable_rx_interrupt(uint8_t uartNo)
{
    uart_inst_t *uart = uart_get_instance(uartNo);
    irq_set_exclusive_handler(UART_IRQ_NUM(uart), uartNo==0 ? uart_rx_interrupt0 : uart_rx_interrupt1);
    irq_set_enabled(UART_IRQ_NUM(uart), true);
    uart_set_irq_enables(uart, true, false);
}
