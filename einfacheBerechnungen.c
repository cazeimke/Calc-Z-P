#include "einfacheBerechnungen.h"
#include "ZeLib/WindowManager.h"

// --- Öffentliche (externe) Funktion für die Ergebnisanzeige ---
/**
 * @brief Löscht die Ergebniszeile und schreibt ein neues Ergebnis.
 * @param result Das Ergebnis als String.
 */
void showResult(char* result) {
    gotoxy(0, RESULT_Y);
    printf("                                                                  ");
    gotoxy(0, RESULT_Y);
    if(strlen(result) > 0) {
        printf("%s: %s", localizedStrings[2][lang], result);
    }
}

// --- Statische (interne) Funktion für die Berechnung ---
static void einfacheBerechnung_calc(EinfacheBerechnungState* state) {
    double num1, num2, ergebnis;
    char operator;
    int itemsParsed;

    itemsParsed = sscanf(state->eingabePuffer, "%lf%c%lf", &num1, &operator, &num2);

    if (itemsParsed != 3) {
        showResult("");
        return;
    }

    switch (operator) {
        case '+': ergebnis = num1 + num2; break;
        case '-': ergebnis = num1 - num2; break;
        case '*': ergebnis = num1 * num2; break;
        case '/':
            if (num2 == 0) {
                showResult(localizedStrings[13][lang]);
                return;
            }
            ergebnis = num1 / num2;
            break;
        default:
            showResult("");
            return;
    }

    char resultString[50];
    sprintf(resultString, "%.4f", ergebnis);
    showResult(resultString);
}


// --- Öffentliche (externe) Funktionen ---

void einfacheBerechnung_init(EinfacheBerechnungState* state) {
    state->pufferGroesse = 20;
    state->eingabePuffer = (char*)malloc(state->pufferGroesse * sizeof(char));
    if (state->eingabePuffer == NULL) {
        showResult(localizedStrings[14][lang]);
        exit(1);
    }
    state->eingabePuffer[0] = '\0';
    state->pufferIndex = 0;
    state->currentNumberDot = 0;
}

void einfacheBerechnung_handleInput(EinfacheBerechnungState* state, char input) {
    int pufferWurdeGeaendert = 0;

    if (input == 0) {
        gotoxy(0, TITLE_Y);
        printf("%s", localizedStrings[6][lang]);
    } else if (isdigit(input) || input == '.' || input == ',' || input == '+' || input == '-' || input == '*' || input == '/') {
        if (input == '+' || input == '-' || input == '*' || input == '/') {
            state->currentNumberDot = 0;
        }
        
        if (input != '.' && input != ',') {
            if (state->pufferIndex >= state->pufferGroesse - 1) {
                state->pufferGroesse *= 2;
                state->eingabePuffer = (char*)realloc(state->eingabePuffer, state->pufferGroesse * sizeof(char));
                if (state->eingabePuffer == NULL) { showResult(localizedStrings[14][lang]); return; }
            }
            state->eingabePuffer[state->pufferIndex++] = input;
            state->eingabePuffer[state->pufferIndex] = '\0';
            pufferWurdeGeaendert = 1;
        } else if ((input == '.' || input == ',' ) && state->currentNumberDot == 0) {
            if(input == ',') input = '.';
            state->currentNumberDot = 1;
            if (state->pufferIndex >= state->pufferGroesse - 1) {
                state->pufferGroesse *= 2;
                state->eingabePuffer = (char*)realloc(state->eingabePuffer, state->pufferGroesse * sizeof(char));
                if (state->eingabePuffer == NULL) { showResult(localizedStrings[14][lang]); return; }
            }
            state->eingabePuffer[state->pufferIndex++] = input;
            state->eingabePuffer[state->pufferIndex] = '\0';
            pufferWurdeGeaendert = 1;
        }
    } else if ((input == '\b' || input == 127) && state->pufferIndex > 0) {
        if (state->eingabePuffer[state->pufferIndex - 1] == '.') {
            state->currentNumberDot = 0;
        }
        state->eingabePuffer[--state->pufferIndex] = '\0';
        pufferWurdeGeaendert = 1;
    }

    gotoxy(0, INPUT_Y);
    printf("%s:                                                    ", localizedStrings[1][lang]);
    gotoxy(INPUT_X_START, INPUT_Y);
    printf("%s", state->eingabePuffer);
    gotoxy(INPUT_X_START + state->pufferIndex, INPUT_Y);

    if (pufferWurdeGeaendert) {
        einfacheBerechnung_calc(state);
    }
}