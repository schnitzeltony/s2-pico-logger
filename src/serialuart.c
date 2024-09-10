#include "serialuart.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#define QUEUE_SIZE 32

queue_t rx_queues[NUM_UARTS];
queue_t tx_queues[NUM_UARTS];

static void uart0_interrupt();
static void uart1_interrupt();
static void handleTx(uint8_t uartNo);

void serial_uart_enable_interrupt(uint8_t uartNo)
{
    uart_inst_t *uart = uart_get_instance(uartNo);
    irq_set_exclusive_handler(UART_IRQ_NUM(uart), uartNo==0 ? uart0_interrupt : uart1_interrupt);
    irq_set_enabled(UART_IRQ_NUM(uart), true);
    uart_set_irqs_enabled(uart, true, true);
}

void serial_uart_init(uint8_t uartNo, uint32_t baudrate, uint8_t rxPin, uint8_t txPin)
{
    queue_init(&rx_queues[uartNo], 1, QUEUE_SIZE);
    queue_init(&tx_queues[uartNo], 1, QUEUE_SIZE);

    uart_inst_t *uart = uart_get_instance(uartNo);
    uart_init(uart, baudrate);

    gpio_set_function(txPin, UART_FUNCSEL_NUM(uart, txPin));
    gpio_set_function(rxPin, UART_FUNCSEL_NUM(uart, rxPin));

    uart_set_hw_flow(uart, false, false);
    uart_set_format(uart, 8, 1, UART_PARITY_NONE);

    serial_uart_enable_interrupt(uartNo);
}

void startTransmitAfterAddingTransmitData(uint8_t uartNo)
{
    uart_inst_t *uart = uart_get_instance(uartNo);
    assert(uart_is_enabled(uart));
    uart_set_irqs_enabled(uart, true, false);
    handleTx(uartNo);
    uart_set_irqs_enabled(uart, true, true);
}

queue_t *getRxQueue(uint8_t uartNo)
{
    assert(uartNo < NUM_UARTS);
    return &rx_queues[uartNo];
}

queue_t *getTxQueue(uint8_t uartNo)
{
    assert(uartNo < NUM_UARTS);
    return &tx_queues[uartNo];
}

static void handleRx(uint8_t uartNo)
{
    uart_inst_t *uart = uart_get_instance(uartNo);
    queue_t *rx_queue = &rx_queues[uartNo];
    while(uart_is_readable(uart) && !queue_is_full(rx_queue)) {
        uint8_t character = uart_getc(uart);
        queue_try_add(rx_queue, &character);
    }
}

static void handleTx(uint8_t uartNo)
{
    uart_inst_t *uart = uart_get_instance(uartNo);
    queue_t *tx_queue = &tx_queues[uartNo];
    while(!queue_is_empty(tx_queue) && uart_is_writable(uart)) {
        uint8_t character;
        queue_try_remove(tx_queue, &character);
        uart_putc(uart, character);
    }
}

static void uart0_interrupt()
{
    handleRx(0);
    handleTx(0);
}

static void uart1_interrupt()
{
    handleRx(1);
    handleTx(1);
}
