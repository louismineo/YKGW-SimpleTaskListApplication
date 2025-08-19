#include <windows.h>

#define CONSOLE_BLACK       0
#define CONSOLE_BLUE        1
#define CONSOLE_GREEN       2
#define CONSOLE_CYAN        3
#define CONSOLE_RED         4
#define CONSOLE_MAGENTA     5
#define CONSOLE_BROWN       6
#define CONSOLE_GRAY        7  // light gray (normal)

#define CONSOLE_DARK_GRAY   8
#define CONSOLE_BRIGHT_BLUE 9
#define CONSOLE_BRIGHT_GREEN 10
#define CONSOLE_BRIGHT_CYAN  11
#define CONSOLE_BRIGHT_RED   12
#define CONSOLE_BRIGHT_MAGENTA 13
#define CONSOLE_YELLOW       14
#define CONSOLE_WHITE        15

class Console {
public:
    static HANDLE hConsole;

    static void setColor(int color) {
        SetConsoleTextAttribute(hConsole, color);
    }
};

// initialize global handle
HANDLE Console::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);