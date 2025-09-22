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
    return _getch();
#else
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(STDIN_FILENO, &old) < 0) perror("tcgetattr()");
    struct termios new_settings = old;
    new_settings.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_settings) < 0) perror("tcsetattr ICANON");
    if (read(STDIN_FILENO, &buf, 1) < 0) perror("read()");
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0) perror("tcsetattr ~ICANON");
    return buf;
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