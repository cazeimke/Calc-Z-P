#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

// --- Standard Headers ---
#include <stdio.h>
#include  <string.h>

// --- Platform-specific Headers ---
#ifdef _WIN32
    #include <windows.h> // Hinzugefügt für gotoxy()
#endif

// --- Structures ---
typedef struct {
    int x;
    int y;
} windowManager_pointer;

typedef struct {
    char* content;
} windowManager_content;

// --- Function Declarations ---

/**
 * @brief Initialising the function with some Data (Console width..)
 */
void WINDOWMANAGER_INIT(void);


/**
 * @brief Sets the cursor position on the console.
 * @param x The horizontal coordinate (column).
 * @param y The vertical coordinate (row).
 */
void gotoxy(int x, int y);


/**
 * @brief Writes Content on a given Position on the Console screen
 * @param wmp An "windowManager_ponter" element (The Position of the Content)
 * @param wmc The Content that has to be writen
 */
int writeOnDisplay (const windowManager_pointer *wmp,const windowManager_content *wmc);


#endif // WINDOW_MANAGER_H
