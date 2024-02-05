#include "headers/defs.h"
#include "headers/console.h"
#include "headers/types.h"

void entry()
{
    int c;
    int progress = 0;
    uart_init();
    puts(CLEAR_SCREEN CURSOR_UP_LEFT); /* Clear screen and move cursor to 1,1 */
    welcomeScreen();

    printf("Hello World!\n");
    printf("%d\n", 123);

    printf("Ponteiro falso: %p\n endereço de c %p\n Binario %b\n Caracter %c\n", 0x1234, &c, 3, 'a');
    printf("%\n");

    for (;;)
    {
        c = uart_getc();
        if (c == -1)
            continue;

        switch (c)
        {
        case '\r':           /* Enter - 13 */
            uart_putc('\r'); /* Carriage return */
            uart_putc('\n'); /* New line */
            break;

        case 127:            /* Backspace - '\b' */
            uart_putc('\b'); /* move the cursor to the left */
            uart_putc(' ');  /* delete the last character */
            uart_putc('\b'); /* move the cursor to the left again */
            break;

        case 110: /* 'n' */
            progress++;
            displayProgressBar(progress);
            break;

        default:
            uart_putc(c);
        }
    }
}