#include "binaryFunction.h"

NUMBERS nmbrs;
int selInp;


/**
 * @brief Initialising the function "Binary Operations"
 */
void binaryFunction_init (void){
    selInp = 0;
    nmbrs.mode = 0;
    strcpy(nmbrs.first, "0000 0000");
    strcpy(nmbrs.second, "0000 0000");
    strcpy(nmbrs.result, "0000 0000");
    strcpy(nmbrs.modeStr, " AND ");
}





void construct_WindowManager(windowManager_pointer *wm, windowManager_content *wmc, int x, int y, char* text){
    wm->x = y;
    wm->y = x;
    wmc->content = text;
}


void binOp(NUMBERS* nmb, int mode){


    for(int i = 0; i < 9; i++){
        
        if(i == 4){
            (*nmb).result[i] = ' ';
        continue;
        }  
        
        switch(mode){
            //      AND
            case 0: 
                (*nmb).result[i] = 
                ( (*nmb).first[i] == '1' && (*nmb).second[i] == '1' )
                    ? '1' : '0';  
            break;
            //      OR
            case 1: 
                (*nmb).result[i] = 
                ( (*nmb).first[i] == '0' && (*nmb).second[i] == '0' ) 
                    ? '0' : '1';
            break;
            //      NOT
            case 2: 
                (*nmb).result[i] = 
                (*nmb).first[i] == '0' ? '1' : '0';              
            break;
            //      XOR
            case 3: 
                (*nmb).result[i] = 
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
}
    

//      Startpunkt      -   Aufruf nach jedem Tastendruch
//  Bei Erstaufruf aus Menü nach Wechsel von CURRENT_WINDOW die Funktion mit input 'n' initialisieren.

void binaryMain(
    const int header_x, const int content_x, const int input_x,
    const int input_y,  const int footer_x, const char input) 
{    
    windowManager_pointer wm;
    windowManager_content wmc; 
    
    

    //      Header beschriften - langString[7][lang]
    construct_WindowManager(&wm, &wmc, header_x, 0, "Binäre Operationen"); 
    writeOnDisplay(&wm, &wmc);


    //      Anzeige des ausgewählten Blocks
    construct_WindowManager(&wm, &wmc, selInp ? input_x + 1 : input_x, input_y - 2, ">");         // Ist INPUT_Y > 2?
    writeOnDisplay(&wm, &wmc);   


    //      Anzeige des erstem Input-Block mit Operator-String
    construct_WindowManager(&wm, &wmc, input_x, input_y, nmbrs.first);
    writeOnDisplay(&wm, &wmc);

    //      Anzeige des erstem Input-Block mit Operator-String
    construct_WindowManager(&wm, &wmc, input_x, input_y + 9, nmbrs.modeStr);
    writeOnDisplay(&wm, &wmc);
    


    //      Anzeige des zweiten Input-Block

    construct_WindowManager(&wm, &wmc, input_x + 1, input_y, nmbrs.mode != 2 ?  nmbrs.second : "---------");
    writeOnDisplay(&wm, &wmc);   

    
    switch (input)
    {
        case '0':
            bitwiseLeftStr( selInp == 0   ?  nmbrs.first : nmbrs.second, '0');
        break;

        case '1':
            bitwiseLeftStr( selInp == 0   ?   nmbrs.first : nmbrs.second, '1');
        break;
        

        case '\n':                                     
            selInp = !selInp;   
        break;
        case '\t':                                     
            nmbrs.mode = ( nmbrs.mode != 3 ) ? nmbrs.mode + 1 : 0;            
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

        default:
        break;
    }



    //      Berechnung aus dem Struct
    binOp(&nmbrs, nmbrs.mode);

    //      Ergebnis-Block
    construct_WindowManager(&wm, &wmc, input_x + 3, input_y, nmbrs.result); 
    writeOnDisplay(&wm, &wmc);   
}
