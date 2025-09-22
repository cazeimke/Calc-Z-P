#include <stdio.h>
#include <string.h>

typedef struct {
    int x;
    int y;
//    int currentPosition;
} windowManager_pointer;

typedef struct {
//    int type;
    char* content;
//    int x;
//    int y;
} windowManager_content;


char getNonBlockingInput(){
//    return "a";
}

void SleepSeconds(){}




/*
        Weitere Operatoren: 
            XOR     nur 1 wenn A != B 
            NAND    nur 0 wenn A == B
            NOR     Negativ OR

        Vllt: Rekursive Funktion
*/




typedef struct
{
    char first[10];                       //    Erste Binärzahl
    char second[10];                      //    Zweite Binärzahl
    char result[10];                      //    Ergebnis in Binär
    int     mode;                         //    Operatorauswahl:  0 = AND; 1 = OR; 2 = NOT; 3 = XOR
    char    modeStr[5];                   //    OperatorString: " AND", " OR ", " NOT", " XOR"
}NUMBERS;



/*      struct nmbrs
            first   -   char[10] Erster Binärblock       "0000 0000"
            second  -   char[10] Zweiter Binärblock      "0000 0000"
            result  -   char[10] Ergebnisblock           "0000 0000"
            mode    -   Aktueller Operand (Default AND)   0
            modeStr -   char[5] der den Modus darstellt   " AND"
*/

                              



//      Helper Funktion, die den WindowManager Struct auffüllt
void construct_WindowManager(windowManager_pointer wm, windowManager_content wmc, int x, int y, char* text){
    wm.x = x;
    wm.y = y;
    wmc.content = text;
}








void binaryOperation(NUMBERS* nmb, int mode){


    for(int i = 0; i < 9; i++){
        
        if(i == 4){
            (*nmb).result[i] = ' ';
        continue;
        }  
        
        switch(mode){

            //      AND
            case 0: (*nmb).result[i] = 
                    ( (*nmb).first[i] == '1' && (*nmb).second[i] == '1' )
                    ? '1' : '0';  
            break;
    
            //      OR
            case 1: (*nmb).result[i] = 
                    ( (*nmb).first[i] == '0' && (*nmb).second[i] == '0' ) 
                    ? '0' : '1';
            break;
    

            //      NOT
            case 2: (*nmb).result[i] = 
                    (*nmb).first[i] == '0' ? '1' : '0';              
            break;



            //      XOR
            case 3: (*nmb).result[i] = 
                    ( (*nmb).first[i] != (*nmb).second[i] ) ? '1' : '0';    
            break;


            default: 
            break;


}}}








//      Nimmt charArray[10], verschiebt um 1 nach links und setzt value ein 
void bitwiseLeftStr(char* binaryString, char value){

    for (int i = 0; i < 8; i++)
    {
        if(i < 3  || i > 4)
                    binaryString[i] = binaryString[i+1];

        else if (i == 3)
                    binaryString[i] = binaryString[i+2];

        else if (i == 4)
                    continue;
    }

    binaryString[8] = value;

    #pragma region Alte Funktion

        /*
        if(i == 3)      
                        binaryString[i] = binaryString[i+2];

        else if (i == 4) 
                        continue;

        else            
                        binaryString[i] = binaryString[i+1];
        */

    #pragma endregion

}
    









//      Startpunkt      -   Aufruf nach jedem Tastendruch
//  Bei Erstaufruf aus Menü nach Wechsel von CURRENT_WINDOW die Funktion mit input 'n' initialisieren.

void BinäreOperation(
    void (*wmfunc)(windowManager_pointer, windowManager_content), 
    const int header_x, const int content_x, const int input_x,
    const int input_y,  const int footer_x, const char input) 
{

#pragma region  Variablen deklarieren
    
    windowManager_pointer wm;
    windowManager_content wmc; 


    int selInp;
    NUMBERS nmbrs;

#pragma endregion



#pragma region  Input-Auswertung

    switch (input)
    {
        case '0':
            bitwiseLeftStr( selInp == 0   ?  nmbrs.first : nmbrs.second, '0');
        break;

        case '1':
            bitwiseLeftStr( selInp == 0   ?   nmbrs.first : nmbrs.second, '1');
        break;
        

        case '\n':                                      // Enter zum Wechsel des Feldes
            selInp = !selInp;   //oder ~selInp;
            // selInp = selInp == 0 ? 1 : 0;
        break;


        case '\t':                                      // Eingabe für Operationswechsel
            nmbrs.mode = 
                ( nmbrs.mode != 3 ) ? nmbrs.mode++ : 0;            
            


            switch(nmbrs.mode){

                case 0:
                    strcpy(nmbrs.modeStr, " AND");
                break;


                case 1:
                    strcpy(nmbrs.modeStr, " OR ");
                break;


                case 2:
                    strcpy(nmbrs.modeStr, " NOT");
                break;


                case 3:
                    strcpy(nmbrs.modeStr, " XOR");
                break;


                default:
                break;
            } 
        break;


        case 'n':                                       // n bei Aufruf der Funktion nach Funktionswechsel (Platzhalter)
            selInp = 0;
            nmbrs.mode = 0;

            strcpy(nmbrs.first, "0000 0000");
            strcpy(nmbrs.second, "0000 0000");
            strcpy(nmbrs.result, "0000 0000");
            strcpy(nmbrs.modeStr, " AND ");

        break;



        default:
        break;
    }



#pragma endregion



#pragma region  Zeichnung des Frames

    //      Header beschriften - langString[7][lang]
    construct_WindowManager(wm, wmc, header_x, 0, "Binäre Operationen"); 
    wmfunc(wm, wmc);


    //      Anzeige des ausgewählten Blocks
    construct_WindowManager(wm, wmc, selInp ? input_x + 1 : input_x, input_y - 2, ">");         // Ist INPUT_Y > 2?
    wmfunc(wm, wmc);    


    //      Anzeige des erstem Input-Block mit Operator-String
    construct_WindowManager(wm, wmc, input_x, input_y, strcat(nmbrs.first, nmbrs.modeStr));
    wmfunc(wm, wmc);


    //      Anzeige des zweiten Input-Block
    construct_WindowManager(wm, wmc, input_x + 1, input_y, ( nmbrs.mode =! 2 ) ?  nmbrs.second : "---------");
    wmfunc(wm, wmc);

#pragma endregion



#pragma region  Ausführung und Darstellung des Ergebnis der Operation

    //      Berechnung aus dem Struct
    binaryOperation(&nmbrs, nmbrs.mode);
    

    //      Ergebnis-Block
    construct_WindowManager(wm, wmc, input_x + 3, input_y, nmbrs.result); 
    wmfunc(wm, wmc);

#pragma endregion




#pragma region  Footer

    construct_WindowManager(wm, wmc, footer_x, 0, "langString[ ][lang]"); 
    wmfunc(wm, wmc);

#pragma endregion


}
