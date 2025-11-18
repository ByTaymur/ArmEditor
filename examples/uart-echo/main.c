/**
 * UART Echo Example
 * Receives data and echoes it back
 */

#include <stdint.h>

#define RCC_BASE      0x40023800
#define GPIOA_BASE    0x40020000
#define USART2_BASE   0x40004400

#define RCC_AHB1ENR   *((volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR   *((volatile uint32_t *)(RCC_BASE + 0x40))

#define GPIOA_MODER   *((volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFR0    *((volatile uint32_t *)(GPIOA_BASE + 0x20))

#define USART2_SR     *((volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR     *((volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR    *((volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1    *((volatile uint32_t *)(USART2_BASE + 0x0C))

// Globals for monitoring
volatile uint32_t rx_count = 0;
volatile uint32_t tx_count = 0;
volatile char last_char = 0;

void uart_init(uint32_t baudrate) {
    // Enable GPIOA and USART2 clocks
    RCC_AHB1ENR |= (1 << 0);  // GPIOA
    RCC_APB1ENR |= (1 << 17); // USART2

    // Configure PA2 (TX) and PA3 (RX) as alternate function
    GPIOA_MODER &= ~(0xF << 4);  // Clear PA2-PA3
    GPIOA_MODER |= (0xA << 4);   // AF mode

    // Set alternate function 7 (USART2)
    GPIOA_AFR0 &= ~(0xFF << 8);
    GPIOA_AFR0 |= (0x77 << 8);

    // Configure USART2
    // Assuming 16 MHz clock, for 115200 baud:
    // USARTDIV = 16MHz / 115200 = 138.88 ≈ 139
    USART2_BRR = 139;

    // Enable TX, RX, and USART
    USART2_CR1 = (1 << 13) | (1 << 3) | (1 << 2);
}

void uart_putc(char c) {
    // Wait for TX buffer empty
    while (!(USART2_SR & (1 << 7)));

    USART2_DR = c;
    tx_count++;
}

char uart_getc(void) {
    // Wait for data
    while (!(USART2_SR & (1 << 5)));

    char c = USART2_DR & 0xFF;
    rx_count++;
    last_char = c;
    return c;
}

void uart_puts(const char *str) {
    while (*str) {
        uart_putc(*str++);
    }
}

int main(void) {
    uart_init(115200);

    uart_puts("UART Echo Ready!\r\n");
    uart_puts("Type something...\r\n");

    while (1) {
        char c = uart_getc();

        // Echo back
        uart_putc(c);

        // Newline handling
        if (c == '\r') {
            uart_putc('\n');
        }
    }

    return 0;
}
