#ifndef ZCBASE_H
#define ZCBASE_H

#include <stdio.h>


#ifdef _WIN32
    #include <stdlib.h>  
    #include <conio.h>   
#else
    #include <stdlib.h>  
    #include <unistd.h>  
    #include <termios.h> 
    #include <sys/select.h>
    #include <fcntl.h>
#endif


/**
 * @brief Pauses the program for a specified number of seconds.
 * @param seconds The number of seconds to sleep.
 */
void SleepSeconds(int seconds);

/**
 * @brief Pauses the program for a specified number of milliseconds.
 * @param milliseconds The number of milliseconds to sleep.
 */
void SleepMSeconds(int milliseconds);

/**
 * @brief Clears the console screen.
 * This function uses a platform-specific command to clear the terminal.
 */
void clearConsole();

/**
 * @brief Reads a single character from the console without waiting for a newline.
 * This function returns a character as soon as a key is pressed.
 *
 * @return The character read from the console.
 */
char getChar(void);

/**
 * @brief Checks if a key has been pressed on the keyboard.
 * This function is non-blocking and returns immediately.
 *
 * @return 1 if a key has been pressed, 0 otherwise.
 */
int kbhit(void);


/**
 * @brief Reads a single character from the console without waiting for a newline.
 * This function returns a character as soon as a key is pressed.
 *
 * @return The character read from the console.
 */
char getNonBlockingInput(void);

#endif // ZCBASE_H