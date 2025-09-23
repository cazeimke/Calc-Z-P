
typedef struct
{
    char first[10];                       //    Erste Binärzahl
    char second[10];                      //    Zweite Binärzahl
    char result[10];                      //    Ergebnis in Binär
    int     cursor[2];                    //    Integer, der die bereits gefüllte Menge einer Zahl angibt
    int     mode;                         //    Operatorauswahl:  0 = AND; 1 = OR; 2 = NOT; 3 = XOR
    char    modeStr[5];                   //    OperatorString: " AND", " OR ", " NOT", " XOR"
}NUMBERS;

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


void construct_WindowManager(windowManager_pointer wm, windowManager_content wmc, int x, int y, char* text);


void binaryOperation(NUMBERS* nmb, int mode);

void bitwiseLeftStr(char* binaryString, int cursor, char value);

void binaryMain(
    void (*wmfunc)(windowManager_pointer, windowManager_content), 
    const int header_x, const int content_x, const int input_x,
    const int input_y,  const int footer_x, const char input);