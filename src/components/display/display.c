#include "../../headers/defs.h"
#include "../../headers/console.h"

void displayProgressBar(int progress)
{
    if (progress == 1)
    {
        puts("\n");
    }

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
    }

    puts(RESET_COLOR BOLD CYAN "]");
    puts(RESET_COLOR);
    puts("\n");
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