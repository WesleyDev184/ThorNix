#include "../../headers/defs.h"
#include "../../headers/console.h"

/**
 * Displays a progress bar based on the given progress value.
 *
 * @param progress The progress value (between 0 and 10).
 */
void displayProgressBar(int progress)
{
    if (progress == 1)
    {
        puts("\n");
    }

    // Overwrites the previous progress bar
    puts("\033[1A");
    puts(CLEAR_LINE);

    if (progress > 10)
    {
        puts("Progress is full!\n");
        return;
    }

    // Color definitions
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
            puts(colors[colorIndex]); // Color changes every 2 blocks
            puts("■");
        }
        else
            puts(RED "■");
    }

    puts(RESET_COLOR BOLD CYAN "]");
    puts(RESET_COLOR);
    puts("\n");
}

/**
 * Displays the welcome screen of the application.
 */
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