#include "../../headers/memlayout.h"
#include "../../headers/types.h"

#define RBR 0 // Receiver buffer register
#define THR 0 // Transmit Holding Register
#define IER 1 // Interrupt Enable Register
#define FCR 2 // FIFO Control Register
#define LCR 3 // Line Control Register
#define LSR 5 // Line Status Register

/**
 * Reads the value from the specified register.
 *
 * @param reg The register to read from.
 * @return The value read from the register.
 */
char read_reg(uint8 reg)
{
    char c;
    volatile char *base = (char *)UART;
    c = *(base + reg);
    return c;
}

/**
 * Writes the specified value to the specified register.
 *
 * @param reg The register to write to.
 * @param c The value to write.
 */
void write_reg(uint8 reg, char c)
{
    volatile char *base = (char *)UART;
    *(base + reg) = c;
}

/**
 * Initializes the UART by configuring the necessary registers.
 */
void uart_init()
{
    // Enable FIFO
    write_reg(FCR, 1);
    // 8-bit data
    write_reg(LCR, 3);
    // Enable interrupt
    write_reg(IER, 1);
}

/**
 * Reads a character from the UART receive buffer.
 *
 * @return The character read, or -1 if the buffer is empty.
 */
int uart_getc()
{
    char c;
    if ((read_reg(LSR) & 1) == 0)
    {
        return -1;
    }
    c = read_reg(RBR);
    return c;
}

/**
 * Writes a character to the UART transmit buffer.
 *
 * @param c The character to write.
 */
void uart_putc(char c)
{
    while ((read_reg(LSR) & (1 << 5)) == 0)
        ;
    write_reg(THR, c);
}