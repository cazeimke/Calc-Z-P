#include "WindowManager.h"


int _CONSOLE_WIDTH = 0;
int _CONSOLE_HEIGHT = 0;


void WINDOWMANAGER_INIT(void) {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        _CONSOLE_WIDTH = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        _CONSOLE_HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        _CONSOLE_WIDTH = w.ws_col;
        _CONSOLE_HEIGHT = w.ws_row;
    #endif
}



/**
 * @brief Sets the cursor position on the console.
 *
 * This function uses platform-specific methods to move the cursor.
 * On Windows, it uses the Win32 API. On other systems (like Linux/macOS),
 * it sends an ANSI escape code to the terminal.
 *
 * @param x The horizontal coordinate (column).
 * @param y The vertical coordinate (row).
 */
void gotoxy(int x, int y) {
#ifdef _WIN32
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("\033[%d;%dH", y + 1, x + 1);
#endif
}


int writeOnDisplay (const windowManager_pointer *wmp,const windowManager_content *wmc){
    
    gotoxy(
        wmp->x, 
        wmp->y
        );
    printf("%s", wmc->content);
    return 0;
}