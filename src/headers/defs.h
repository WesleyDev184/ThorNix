// UART functions - path: src/drivers/Uart/uart.c
int uart_getc();
void uart_putc(char c);
void uart_init();

// Memory functions - path: src/drivers/Memory/memory.c
void memory_init();
void *kalloc(int pages);

// core functions - path: src/components/core/core.c
void puts(char *s);
void printf(char *format, ...);
void printptr(void *ptr);
void printlng(long int val, int base);

// display functions - path: src/components/display/display.c
void welcomeScreen();
void displayProgressBar(int progress);

// Test Functions - path: src/components/teste/teste_functions.c
int perimeter(int sides, ...);