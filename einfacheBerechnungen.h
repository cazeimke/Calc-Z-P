#ifndef EINFACHE_BERECHNUNGEN_H
#define EINFACHE_BERECHNUNGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "localizedString.h"

// --- Externe Deklarationen für Layout und Sprachvariablen ---
extern const int TITLE_Y;
extern const int INPUT_Y;
extern const int RESULT_Y;
extern const int INPUT_X_START;
//extern int lang;

// --- Externe Deklaration der Konsolenfunktionen ---
extern void gotoxy(int x, int y);

// --- Zustandsstruktur für das Modul ---
typedef struct {
    char* eingabePuffer;
    int pufferGroesse;
    int pufferIndex;
    int currentNumberDot;
} EinfacheBerechnungState;

// --- Funktionsdeklarationen ---
void einfacheBerechnung_init(EinfacheBerechnungState* state);
void einfacheBerechnung_handleInput(EinfacheBerechnungState* state, char input);
void showResult(char* result);

#endif // EINFACHE_BERECHNUNGEN_H