#include "headers/defs.h"
#include "headers/console.h"

void puts(char *s)
{
    while (*s != 0)
    {
        uart_putc(*s++);
    }
}

void welcomeScreen()
{
    puts(BOLD BLACK);
    puts("      ------------------     \n");
    puts("     |                  |    \n");
    puts("     |     Thor Nix     |    \n");
    puts("     |                  |    \n");
    puts("      ------------------     \n");
    puts(BOLD RED);
    puts("             |  |            \n");
    puts("             |  |            \n");
    puts("             |  |            \n");
    puts("             |  |            \n");
    puts("             |  |            \n");
    puts("              --             \n");
    puts(RESET_COLOR RESET_BOLD);
    puts("    Licensed under GPLv3:    \n");
    puts("\n");
}

void displayProgressBar(int progress)
{
    // sobrescreve a barra de progresso anterior
    puts("\033[1A");
    puts(CLEAR_LINE);

    if (progress > 10)
    {
        puts("Progress is full!\n");
        return;
    }

    // Definições de cores
    char *colors[] = {YELLOW, GREEN, CYAN, MAGENTA, BLUE};
    int numColors = sizeof(colors) / sizeof(colors[0]);

    puts(BOLD CYAN);
    puts("Progress: [");

    int i;
    for (i = 0; i < 10; ++i)
    {
        if (i < progress)
        {
            int colorIndex = progress / 2 % numColors;
            puts(colors[colorIndex]); // Troca de cor a cada 2 blocos
            puts("■");
        }
        else
            puts(RED "■");

        if (i == 4)
            puts(RESET_COLOR BOLD CYAN); // Troca de cor após 5 blocos
        else
            puts(RESET_COLOR BOLD CYAN);
    }

    puts(RESET_COLOR BOLD CYAN "]");
    puts(RESET_COLOR);
    puts("\n");
}

void entry()
{
    int c;
    int n = 0; // Variable to control color switching
    int progress = 0;
    uart_init();
    puts(CLEAR_SCREEN CURSOR_UP_LEFT); /* Clear screen and move cursor to 1,1 */
    welcomeScreen();
    displayProgressBar(progress);
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