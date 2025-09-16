#include "localizedString.h"
#include <stdio.h>

void ausgabeStrings();

int main()
{
    system("chcp 65001");

    ausgabeStrings();

    scanf(" %c", NULL);

    return 0;
}

void ausgabeStrings(){
    for (int i = 0; i < 32; i++)
        printf("%d.\t%s - %s\n", i, localizedStrings[i][0], localizedStrings[i][1]);   
}