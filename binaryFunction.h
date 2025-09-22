
#ifndef BINARY_FUNCTION_H
#define BINARY_FUNCTION_H

#include "ZeLib\WindowManager.h"
#include "ZeLib\ZcBase.h"
#include "ZeLib\ZThreading.h"
#include "localizedString.h"

#include <stdio.h>
#include <string.h>

typedef struct
{
    char first[10];                       //    Erste Binärzahl
    char second[10];                      //    Zweite Binärzahl
    char result[10];                      //    Ergebnis in Binär
    int     mode;                         //    Operatorauswahl:  0 = AND; 1 = OR; 2 = NOT; 3 = XOR
    char    modeStr[5];                   //    OperatorString: " AND", " OR ", " NOT", " XOR"
}NUMBERS;



/**
 * @brief Initialising the function "Binary Operations"
 */
void binaryFunction_init (void);


void construct_WindowManager(windowManager_pointer *wm, windowManager_content *wmc, int x, int y, char* text);

void binaryOperation(NUMBERS* nmb, int mode);

void bitwiseLeftStr(char* binaryString, char value);

void binaryMain(

    const int header_x, const int content_x, const int input_x,
    const int input_y,  const int footer_x, const char input);


#endif // BINARY_FUNCTION_H