#include "ZThreading.h"

int THREADING_MAIN_INFINITE = 0;
int THREADING_MAIN_BREAK = 0;

void Threading_Main(
    void (*func)(void),
    int count
){
    if (count == 0) {
        THREADING_MAIN_INFINITE = 1;
    }
    
    // Korrigierte Schleifenlogik
    for (int i = 0; THREADING_MAIN_INFINITE || i < count; i++) {
        func();
        if (THREADING_MAIN_BREAK) {
            break;
        }

        #ifdef _WIN32
            Sleep(20);
        #else
            usleep(20000);
        #endif
    }
}