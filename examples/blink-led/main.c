/**
 * STM32F407 LED Blink Example
 * For ArmEditor IDE
 */

#include <stdint.h>

// STM32F407 Register addresses
#define RCC_BASE      0x40023800
#define GPIOD_BASE    0x40020C00

#define RCC_AHB1ENR   *((volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOD_MODER   *((volatile uint32_t *)(GPIOD_BASE + 0x00))
#define GPIOD_ODR     *((volatile uint32_t *)(GPIOD_BASE + 0x14))

// PD12, PD13, PD14, PD15 = LEDs on STM32F4-Discovery
#define LED_GREEN  (1 << 12)
#define LED_ORANGE (1 << 13)
#define LED_RED    (1 << 14)
#define LED_BLUE   (1 << 15)

// Global variables for debugging
volatile uint32_t counter = 0;
volatile uint32_t led_state = 0;
volatile float temperature = 25.0f;

void delay_ms(uint32_t ms) {
    // Simple delay (assuming 168MHz)
    for (uint32_t i = 0; i < ms * 10000; i++) {
        __asm("nop");
    }
}

void led_init(void) {
    // Enable GPIOD clock
    RCC_AHB1ENR |= (1 << 3);

    // Set PD12-15 as output
    GPIOD_MODER &= ~(0xFF << 24);  // Clear
    GPIOD_MODER |= (0x55 << 24);   // Set as output
}

void led_on(uint32_t led) {
    GPIOD_ODR |= led;
    led_state |= led;
}

void led_off(uint32_t led) {
    GPIOD_ODR &= ~led;
    led_state &= ~led;
}

void led_toggle(uint32_t led) {
    GPIOD_ODR ^= led;
    led_state ^= led;
}

int main(void) {
    led_init();

    while (1) {
        // Blink green LED
        led_toggle(LED_GREEN);
        counter++;

        // Simulate temperature reading
        temperature += 0.1f;
        if (temperature > 30.0f) {
            temperature = 25.0f;
        }

        // Pattern: Green -> Orange -> Red -> Blue
        if (counter % 4 == 0) {
            led_off(LED_GREEN | LED_ORANGE | LED_RED | LED_BLUE);
            led_on(LED_GREEN);
        } else if (counter % 4 == 1) {
            led_off(LED_GREEN | LED_ORANGE | LED_RED | LED_BLUE);
            led_on(LED_ORANGE);
        } else if (counter % 4 == 2) {
            led_off(LED_GREEN | LED_ORANGE | LED_RED | LED_BLUE);
            led_on(LED_RED);
        } else {
            led_off(LED_GREEN | LED_ORANGE | LED_RED | LED_BLUE);
            led_on(LED_BLUE);
        }

        delay_ms(500);
    }

    return 0;
}
