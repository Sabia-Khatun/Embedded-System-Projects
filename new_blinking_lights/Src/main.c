#include <stdint.h>

/* Register Addresses for STM32H563ZITx */
#define RCC_AHB2ENR   ((volatile uint32_t*) 0x44020C8C)
#define GPIOF_MODER   ((volatile uint32_t*) 0x42021400) // Port F Moder
#define GPIOF_ODR     ((volatile uint32_t*) 0x42021414) // Port F Output Data Register

int main(void) {
    /* 1. Enable Clock for Port F */
    // Bit 5 corresponds to GPIOF in the AHB2ENR register
    *RCC_AHB2ENR |= (1 << 5);

    /* 2. Configure PF4 as Output */
    // MODER uses 2 bits per pin. Pin 4 uses bits 9 and 8.
    // Setting bits 9:8 to "01" makes it General Purpose Output.
    *GPIOF_MODER &= ~(3 << 8); // Clear bits 9 and 8
    *GPIOF_MODER |=  (1 << 8); // Set bit 8 to 1 (Output mode)

    /* 3. Blink Loop */
    while (1) {
        // Set Pin 4 HIGH (Turn Yellow LED ON)
        *GPIOF_ODR |= (1 << 4);

        // Delay loop
        for (volatile int i = 0; i < 500000; i++);

        // Set Pin 4 LOW (Turn Yellow LED OFF)
        *GPIOF_ODR &= ~(1 << 4);

        // Delay loop
        for (volatile int i = 0; i < 500000; i++);
    }

    return 0;
}
