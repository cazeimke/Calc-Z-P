#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ZeLib/ZcBase.h"
#include "ZeLib/WindowManager.h"
#include "ZeLib/ZThreading.h"
#include "einfacheBerechnungen.h"
#include "localizedString.h"

// --- Globale Variablen & Konstanten ---
int CURRENT_WINDOW = 0;
int firstRun = 1;
char inputChar;

// Layout-Konstanten
const int TITLE_Y = 3;
const int INPUT_Y = 5;
const int RESULT_Y = 7;
const int INPUT_X_START = 17;
const int FOOTER_Y = 15;    

// Sprachvariable
unsigned char lang = 0;

// Globale Variable für den Zustand der einfachen Berechnung
EinfacheBerechnungState g_einfacheBerechnung;

// --- Funktionsdeklarationen ---
void zeichneRahmen(void);
void einstellungen(void);
void einheitAuswahl(void);
void main_runner(void);
void menu(char input);
void changeCurrentWindow(int window);

// --- Hauptprogramm ---
int main(void) {
    #ifdef _WIN32
        system("chcp 65001");
    #endif


    WINDOWMANAGER_INIT();
    einfacheBerechnung_init(&g_einfacheBerechnung);

    clearConsole();
    zeichneRahmen();
    
    Threading_Main(&main_runner, 0);

    // Aufräumen, wenn die Schleife beendet wird
    free(g_einfacheBerechnung.eingabePuffer);
    g_einfacheBerechnung.eingabePuffer = NULL;

    gotoxy(0, 12);
    printf("%s\n", localizedStrings[15][lang]);
    
    return 0;
}

// --- UI-Funktionen ---
void zeichneRahmen(void) {
    gotoxy(0, 0);
    printf("%s\n", localizedStrings[0][lang]);
    printf("------------------------------------------------------------------\n");
    
    gotoxy(0, 15);
    printf("------------------------------------------------------------------\n");
    if (CURRENT_WINDOW == 4) {
        printf("q = %s\tb = %s\tm = %s", localizedStrings[3][lang], localizedStrings[17][lang], localizedStrings[4][lang]);
    } else {
        printf("q = %s\t\tm = %s", localizedStrings[3][lang], localizedStrings[4][lang]);
    }
}

void einstellungen(void) {
    gotoxy(0, TITLE_Y);
    printf("%s > %s", localizedStrings[4][lang], localizedStrings[9][lang]);

    gotoxy(0, INPUT_Y);
    char txt[30];
    if(lang) {
        sprintf(txt, "1. %s\n2. [%s]", localizedStrings[11][0], localizedStrings[11][1]);
    } else {
        sprintf(txt, "1. [%s]\n2. %s", localizedStrings[11][0], localizedStrings[11][1]);
    }
    printf("%s\t\n%s", localizedStrings[10][lang], txt);
}

void menu(char input) {
    gotoxy(0, TITLE_Y);
    printf("%s", localizedStrings[4][lang]);
    gotoxy(0, TITLE_Y + 2);
    printf("%s:", localizedStrings[5][lang]);
        
    gotoxy(0, TITLE_Y + 3);
    printf("1 = %s", localizedStrings[6][lang]);

    gotoxy(0, TITLE_Y + 4);
    printf("2 = %s", localizedStrings[7][lang]);

    gotoxy(0, TITLE_Y + 5);
    printf("3 = %s", localizedStrings[8][lang]);

    gotoxy(0, TITLE_Y + 6);
    printf("4 = %s (%s)", localizedStrings[9][lang], localizedStrings[10][lang]);

    switch (input) {
        case '1':
            changeCurrentWindow(1);
            einfacheBerechnung_handleInput(&g_einfacheBerechnung, 0);
            break;
        case '2':
            changeCurrentWindow(2);
            break;
        case '3':
            break;
        case '4':
            changeCurrentWindow(4);
            einstellungen();
            break;
        default:
            break;
    }
}

void changeCurrentWindow(int window) {
    clearConsole();
    zeichneRahmen();
    CURRENT_WINDOW = window;
}

// --- Hauptschleife ---
void main_runner(void) {
    if (kbhit() || firstRun) {
        inputChar = firstRun ? 0 : getNonBlockingInput();
        firstRun = 0;

        if (inputChar == 'q') {
            THREADING_MAIN_BREAK = 1;
        }
        if (inputChar == 'm') {
            changeCurrentWindow(0);
        }
        if (inputChar == 'b' && CURRENT_WINDOW == 4) {
            changeCurrentWindow(0);
        }

        switch (CURRENT_WINDOW) {
            case 0:
                menu(inputChar);
                break;
            case 1:
                einfacheBerechnung_handleInput(&g_einfacheBerechnung, inputChar);
                break;
            case 2:
                binaryMain(TITLE_Y, RESULT_Y, INPUT_Y,INPUT_X_START, FOOTER_Y, inputChar);

                break;
            case 3:
                // ...
                break;
            case 4:
                if (inputChar == '1' || inputChar == '2') {
                    lang = inputChar - '1';
                    changeCurrentWindow(4);
                    einstellungen();
                }
                break;
        }
    }
}