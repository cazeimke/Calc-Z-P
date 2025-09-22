#ifndef ZTHREADING_H
#define ZTHREADING_H

// --- Standard Headers ---
#include "ZcBase.h"
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

extern int THREADING_MAIN_INFINITE;
extern int THREADING_MAIN_BREAK;

void Threading_Main(
    void (*func)(void),
    int count);


#endif // ZTHREADING_H
