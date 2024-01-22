// Purpose: Define console escape sequences for formatting and colors.

// Formatting
#define CLEAR_SCREEN "\033[2J"     // clear screen escape sequence
#define CURSOR_UP_LEFT "\033[1;1H" // move cursor to position 1,1
#define BOLD "\033[1m"             // bold escape sequence
#define RESET_BOLD "\033[0m"       // reset bold escape sequence
#define CLEAR_LINE "\033[K"

// Foreground Colors
#define GREEN "\033[38;2;57;255;20m"
#define RED "\033[38;2;255;0;0m"
#define BLUE "\033[38;2;0;0;255m"
#define YELLOW "\033[38;2;255;255;0m"
#define MAGENTA "\033[38;2;255;0;255m"
#define CYAN "\033[38;2;0;255;255m"
#define WHITE "\033[38;2;255;255;255m"
#define BLACK "\033[38;2;0;0;0m"
#define RESET_COLOR "\033[0m"

// Background Colors
#define BG_GREEN "\033[48;2;57;255;20m"
#define BG_RED "\033[48;2;255;0;0m"
#define BG_BLUE "\033[48;2;0;0;255m"
#define BG_YELLOW "\033[48;2;255;255;0m"
#define BG_MAGENTA "\033[48;2;255;0;255m"
#define BG_CYAN "\033[48;2;0;255;255m"
#define BG_WHITE "\033[48;2;255;255;255m"
#define BG_BLACK "\033[48;2;0;0;0m"
