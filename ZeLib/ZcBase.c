#include "ZcBase.h"



#ifdef _WIN32
    #include <windows.h> // Für Sleep() in Millisekunden
#else
    #include <unistd.h> // Für sleep() in Sekunden
#endif

/**
 * @brief Clears the console screen.
 * This function uses a platform-specific command to clear the terminal.
 */
void clearConsole(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Reads a single character from the console without waiting for a newline.
 * This function returns a character as soon as a key is pressed.
 *
 * @return The character read from the console.
 */
char getNonBlockingInput(void) {
#ifdef _WIN32
    if (_kbhit()) {
        return _getch();
    } else {
        return 0; // Kein Zeichen verfügbar
    }
#else
    char buf = 0;
    struct termios old = {0};
    struct termios new_settings = {0};
    int oldf = 0;

    // Terminal-Einstellungen speichern und ändern
    tcgetattr(STDIN_FILENO, &old);
    new_settings = old;
    new_settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

    // Dateideskriptor auf nicht-blockierend setzen
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    read(STDIN_FILENO, &buf, 1);

    // Terminal-Einstellungen zurücksetzen
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return buf; // Gibt 0 zurück, wenn kein Zeichen gelesen wurde
#endif
}

/**
 * @brief Pauses the program for a specified number of seconds.
 *
 * This function uses a platform-specific API to halt the execution
 * for the given duration.
 *
 * @param seconds The number of seconds to sleep.
 */
void SleepSeconds(int seconds) {
    #ifdef _WIN32
        // Windows' Sleep() expects milliseconds, so we convert.
        Sleep(seconds * 1000);
    #else
        // Linux/macOS' sleep() expects seconds.
        sleep(seconds);
    #endif
}


/**
 * @brief Pauses the program for a specified number of milliseconds.
 *
 * This function uses a platform-specific API to halt the execution
 * for the given duration.
 *
 * @param milliseconds The number of milliseconds to sleep.
 */
void SleepMSeconds(int milliseconds){
    #ifdef _WIN32
        // Windows' Sleep() expects milliseconds, so we convert.
        Sleep(milliseconds);
    #else
        // Linux/macOS' sleep() expects seconds.
        sleep(milliseconds / 1000);
    #endif
}


/**
 * @brief Checks if a key has been pressed on the keyboard.
 * This function is non-blocking and returns immediately.
 *
 * @return 1 if a key has been pressed, 0 otherwise.
 */
int kbhit(void) {
#ifdef _WIN32
    return _kbhit();
#else
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return (FD_ISSET(STDIN_FILENO, &fds));
#endif
}