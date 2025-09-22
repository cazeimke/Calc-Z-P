#pragma region --- Bibliotheken einbinden ---

    #include <stdio.h>
    #include <stdlib.h> // Für malloc, realloc, free, atof
    #include <string.h>
    #include <ctype.h>

    #include "localizedString.h" // Sprachvariablen localizedStrings[0-32][0-1]
    #include "binaryFunction.h"

#pragma endregion




#pragma region --- Präprozessor-Anweisungen ---

    #ifdef _WIN32
        #include <conio.h>
        #include <windows.h>
    #else
        #include <unistd.h>
        #include <termios.h>
        #include <sys/select.h>
    #endif

#pragma endregion


#pragma region --- Funktionsprototypen ---

    void gotoxy(int x, int y);
    void clearConsole(void);
    char getChar(void);
    int kbhit(void);

    void zeichneRahmen(void);
    void showResult(char* result);
    void einfacheBerechnung(char input);
    void einfacheBerechnung_calc(void);
    void einstellungen();

    void menu(char input);
    void changeCurrentWindow(int window);
    void einheitAuswahl();

#pragma endregion


#pragma region --- Globale Variablen & Konstanten ---

    int CURRENT_WINDOW = 1;

    // Layout-Konstanten
    const int TITLE_Y = 3;
    const int INPUT_Y = 5;
    const int RESULT_Y = 7;
    const int INPUT_X_START = 17;

    // Globaler, dynamischer Puffer für die Eingabe
    char* g_eingabePuffer = NULL;
    int g_pufferGroesse = 0;
    int g_pufferIndex = 0;
    int g_currentNumberDot = 0;

#pragma endregion



// --- Hauptprogramm ---
int main(void) {
    #ifdef _WIN32
        system("chcp 65001");
    #endif

    char inputChar;
    int firstRun = 1;

    // Initialisierung des globalen Puffers
    g_pufferGroesse = 20;
    g_eingabePuffer = (char*)malloc(g_pufferGroesse * sizeof(char));
    if (g_eingabePuffer == NULL) {
        printf("%s", localizedStrings[14][lang]);                            // "Fehler bei Speicherreservierung"
        return 1;
    }
    g_eingabePuffer[0] = '\0';


    changeCurrentWindow(-1);

    while (1) {
        if (kbhit() || firstRun) {
            inputChar = firstRun ? 0 : getChar();
            firstRun = 0;

            
            if (inputChar == 'q')       break; 

            if (inputChar == 'm')       changeCurrentWindow(0);

            if (inputChar == 'b' && 
                CURRENT_WINDOW == 4)    changeCurrentWindow(0);
            

            switch (CURRENT_WINDOW) {
                case 0:                 //Menü
                    menu(inputChar);
                    break;
                    
                case 1:                 //Einfache Berechnung
                    einfacheBerechnung(inputChar);
                    break;





                case 2:                 //Binaer

                    break;








                case 3:                 //Erweiterte Berrechnung
                    //einfacheBerechnung(inputChar);
                    break;






                case 4: // Einstellungen Input
                        switch (inputChar)
                        {
                        case '1':
                            lang = 0;                            
                            break;

                        case '2':
                            lang = 1;

                        
                        default:
                            break;
                        } 

                        changeCurrentWindow(-1);
                        
                        gotoxy(0, TITLE_Y);
                        printf("%s > %s", localizedStrings[4][lang], localizedStrings[9][lang]);          // "Menü > Sprache"
                        einstellungen();

                    break;

                
            }
        }
        #ifdef _WIN32
            Sleep(20);
        #else
            usleep(20000);
        #endif
    }
    
    free(g_eingabePuffer);
    g_eingabePuffer = NULL;

    gotoxy(0, 12);
    printf("%s\n", localizedStrings[15][lang]);                                     // "Programm beendet."
    return 0;
}






#pragma region --- UI-Funktionen ---

    void zeichneRahmen(void) {
        gotoxy(0, 0);
        printf("%s\n", localizedStrings[0][lang]);                                      //  "Herzlich Willkommen..."
        printf("------------------------------------------------------------------\n");
        
        gotoxy(0, 15);
        printf("------------------------------------------------------------------\n");
        if (CURRENT_WINDOW == 4)
        {
            printf("q = %s\tb = %s\tm = %s", localizedStrings[3][lang], localizedStrings[17][lang], localizedStrings[4][lang]);
        }
        else if (CURRENT_WINDOW == 2)
        {
            printf("q = %s\tb = %s\tm = %s\nTAB = %s\t\tEnter = %s", localizedStrings[3][lang], 
                                            localizedStrings[17][lang], 
                                            localizedStrings[4][lang],
                                            localizedStrings[18][lang],
                                            localizedStrings[19][lang]);
        }
        
        
        else printf("q = %s\t\tm = %s", localizedStrings[3][lang], localizedStrings[4][lang]);    // "Beenden" "Menü"
        
                
    }

    void showResult(char* result) {
        gotoxy(0, RESULT_Y);
        printf("                                                            "); // Zeile leeren
        gotoxy(0, RESULT_Y);
        if(strlen(result) > 0) {
            printf("%s: %s", localizedStrings[2][lang], result);                     // "Ergebnis"
        }
    }

#pragma endregion


#pragma region --- Fenster-Logik: Einfache Berechnungen ---

    void einfacheBerechnung(char input) {
        if (input == 0) {
            gotoxy(0, TITLE_Y);
            printf("%s", localizedStrings[6][lang]);                                 // "Einfache Berechnung"
        }

        // Flag, um zu wissen, ob der Puffer geändert wurde
        int pufferWurdeGeaendert = 0;


        if (isdigit(input) || input == '.' || input == ',' || input == '+' || input == '-' || input == '*' || input == '/') {
            if (input == '+' || input == '-' || input == '*' || input == '/')
                g_currentNumberDot = 0;
            
            if (input != '.' && input != ',')
            {
                if (g_pufferIndex >= g_pufferGroesse - 1) 
                {
                    g_pufferGroesse *= 2;
                    g_eingabePuffer = (char*)realloc(g_eingabePuffer, g_pufferGroesse * sizeof(char));
                    if (g_eingabePuffer == NULL) { showResult(localizedStrings[14][lang]); return; }
                }

                g_eingabePuffer[g_pufferIndex++] = input;
                g_eingabePuffer[g_pufferIndex] = '\0';
                pufferWurdeGeaendert = 1;
            } else if ((input == '.' || input == ',' ) && g_currentNumberDot == 0)
            {                                      
                if(input == ',') input = '.';
                g_currentNumberDot = 1;
                if (g_pufferIndex >= g_pufferGroesse - 1) 
                {
                    g_pufferGroesse *= 2;
                    g_eingabePuffer = (char*)realloc(g_eingabePuffer, g_pufferGroesse * sizeof(char));
                    if (g_eingabePuffer == NULL) { 
                        showResult(localizedStrings[14][lang]); //String "Fehler Speicherreservierung" 
                        return; }
                }
                g_eingabePuffer[g_pufferIndex++] = input;
                g_eingabePuffer[g_pufferIndex] = '\0';
                pufferWurdeGeaendert = 1;
            }
        } 
        else if ((input == '\b' || input == 127) && g_pufferIndex > 0) { // Backspace
            if (g_eingabePuffer[g_pufferIndex - 1] == '.')
                g_currentNumberDot = 0;
            g_eingabePuffer[--g_pufferIndex] = '\0';
            pufferWurdeGeaendert = 1;
        } 


        // Eingabezeile neu zeichnen
        gotoxy(0, INPUT_Y);
        printf("%s:                                                 ", localizedStrings[1][lang]); 
        gotoxy(INPUT_X_START, INPUT_Y);
        printf("%s", g_eingabePuffer);
        gotoxy(INPUT_X_START + g_pufferIndex, INPUT_Y);

        // **NEU**: Wenn der Puffer geändert wurde, versuche sofort zu berechnen
        if(pufferWurdeGeaendert) {
            einfacheBerechnung_calc();
        }
    }


    void einfacheBerechnung_calc(void) {
        double num1, num2, ergebnis;
        char operator;
        int itemsParsed;

        itemsParsed = sscanf(g_eingabePuffer, "%lf %c %lf", &num1, &operator, &num2);

        // **NEU**: Wenn die Eingabe nicht dem vollen Format entspricht,
        // wird die Ergebniszeile geleert und die Funktion beendet.
        if (itemsParsed != 3) {
            showResult(""); // Leerer String, um die Zeile zu säubern
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
                showResult(""); // Operator ungültig, Ergebniszeile leeren
                return;
        }

        char resultString[50];
        sprintf(resultString, "%.4f", ergebnis);
        showResult(resultString);
        
    }

#pragma endregion


// Einstellungen
void einstellungen(){

    changeCurrentWindow(-1);
    gotoxy(0, INPUT_Y);

    char txt[30];

    if(lang)
        sprintf(txt, "1. %s\n2. [%s]", localizedStrings[11][0], localizedStrings[11][1]);
    else 
        sprintf(txt, "1. [%s]\n2. %s", localizedStrings[11][0], localizedStrings[11][1]);

    printf("%s\t\n%s", localizedStrings[10][lang], txt);
}






//  Konzeptuell vorerst
void einheitAuswahl(){
    changeCurrentWindow(-1);
    
    gotoxy(0, TITLE_Y );
    printf("1. %s", "Länge (mm cm dm m km)");

    gotoxy(0, TITLE_Y + 1);
    printf("2. %s", "Fläche (mm² cm² m² km²)");
    
    gotoxy(0, TITLE_Y + 2);
    printf("3. %s", "Volumen (mm³ cm³ m³ km³)");

    gotoxy(0, TITLE_Y + 3);
    printf("4. %s", "Flüssigkeit (ml cl l m³)");

    gotoxy(0, TITLE_Y + 4);
    printf("5. %s", "Gewicht (mg g kg)");

    gotoxy(0, TITLE_Y + 5);
    printf("6. %s", "Daten (Bit Byte KB MB GB TB)");



}



// --- Fenster-Logik: Menü ---
void menu(char input){
    gotoxy(0, TITLE_Y );
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

    switch (input)
    {
    case '1':                   //Einfache Berechnungen
        changeCurrentWindow(1);
        printf("%s", localizedStrings[6][lang]);
        einfacheBerechnung('n');
        break;
    



    case '2':                   //Binäre Berechnungen

        changeCurrentWindow(2);
         binaryMain(                    //    Muss noch ordentlich ausgefüllt werden
            void, 0, 0, INPUT_X_START, INPUT_Y, 0, 
            'n');        
        
        break;















    case '3':                   //Umrechnung
        changeCurrentWindow(3);
        //gotoxy(0, TITLE_Y);
        // printf("%s", localizedStrings[8][lang]);

        einheitAuswahl();

        break;



















    case '4':                   //Einstellungen
        changeCurrentWindow(4);
        gotoxy(0, TITLE_Y);
        printf("%s > %s", localizedStrings[4][lang], localizedStrings[9][lang]);
        einstellungen();
        break;

    default:
        break;
    }

}






// window: -1 = nur clearConsole und zeichneRahmen
void changeCurrentWindow(int window){
    if (window != -1)   CURRENT_WINDOW = window;
    clearConsole();
    zeichneRahmen();
}






#pragma region --- Hilfsfunktionen (gotoxy, etc. bleiben unverändert) ---

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
    void clearConsole(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }
    char getChar(void) {
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

#pragma endregion