#include "binaryFunction.h"

NUMBERS nmbrs;
int selInp;


/**
 * @brief Initialising the function "Binary Operations"
 */
void binaryFunction_init (void){
    selInp = 0;
    nmbrs.mode = 0;
    nmbrs.cursor[0] = 0;
    nmbrs.cursor[1] = 0;
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

/**
 * @brief Calculates with the NUMBERS Struct in the given mode
 * @param nmb* NUMBERS struct pointer
 */
void binOp(NUMBERS* nmb){

    for(int i = 0; i < 9; i++){
        
        if(i == 4){
            (*nmb).result[i] = ' ';
        continue;
        }  
        
        switch((*nmb).mode){
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

/**
 * @brief Currently shifts a charArray[10] by 1 to the left and 
 * puts value on the last Index before the terminator
 * @param binaryString The Binary as a Char Array of 10
 * @param value The Value that is being pushed at the last Index 
 **/
void bitwiseLeftStr(char* binaryString, int cursor, char value){


    // Overflow-Zustand wenn letzte Ziffer erreicht ist, danach 
    //Zusatzvariable als Zähler, die bei 0 anfängt

    if(!isdigit(value)) return;

    if (cursor < 9)
    {
        binaryString[cursor] = value;
    } else{
        
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


    
}
    

/**
 * @brief Entry Point of the binary feature
 * @param input Key Input Char 
 **/
void binaryMain(
    const int header_x, const int content_x, const int input_x,
    const int input_y,  const int footer_x, const char input) 
{    
    windowManager_pointer wm;
    windowManager_content wmc; 

    //      Header beschriften - langString[7][lang]
    construct_WindowManager(&wm, &wmc, header_x, 0, localizedStrings[7][lang]);     // TODO Fix the lang situation
    writeOnDisplay(&wm, &wmc);

    if(nmbrs.cursor[selInp] == 4) nmbrs.cursor[selInp] = 5;

    switch (input)
    {
        case '0':
            bitwiseLeftStr( selInp == 0   ?  nmbrs.first : nmbrs.second, (nmbrs.cursor[selInp])++ ,'0');
        break;
        case '1':
            bitwiseLeftStr( selInp == 0   ?   nmbrs.first : nmbrs.second, (nmbrs.cursor[selInp])++, '1');
        break;
        case '\r':                                     
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
    binOp(&nmbrs);

    //      Anzeige des ausgewählten Blocks
    if(selInp == 0){
        construct_WindowManager(&wm, &wmc, input_x, input_y - 2, ">");
        writeOnDisplay(&wm, &wmc);   

        construct_WindowManager(&wm, &wmc, input_x + 1, input_y - 2, " ");
        writeOnDisplay(&wm, &wmc);   
    } else{
        construct_WindowManager(&wm, &wmc, input_x, input_y - 2, " ");
        writeOnDisplay(&wm, &wmc);   

        construct_WindowManager(&wm, &wmc, input_x + 1, input_y - 2, ">");
        writeOnDisplay(&wm, &wmc);   
    }

    //      Anzeige des erstem Input-Block
    construct_WindowManager(&wm, &wmc, input_x, input_y, nmbrs.first);
    writeOnDisplay(&wm, &wmc);

    //      Anzeige des  Operator-String
    construct_WindowManager(&wm, &wmc, input_x, input_y + 9, nmbrs.modeStr);
    writeOnDisplay(&wm, &wmc);

    //      Anzeige des zweiten Input-Block
    construct_WindowManager(&wm, &wmc, input_x + 1, input_y, nmbrs.mode != 2 ?  nmbrs.second : "---------");
    writeOnDisplay(&wm, &wmc);   

    //      Ergebnis-Block
    construct_WindowManager(&wm, &wmc, input_x + 3, input_y, nmbrs.result); 
    writeOnDisplay(&wm, &wmc);  

    //  Bringe Cursor auf Cursor
    construct_WindowManager(&wm, &wmc, selInp ? input_x + 1 : input_x, input_y + nmbrs.cursor[selInp], ""); 
    writeOnDisplay(&wm, &wmc);  
    
}
