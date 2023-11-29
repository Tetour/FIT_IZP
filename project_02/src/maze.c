#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define LINE_BUFFER_SIZE 1024


enum Args {
    HELP = 0,
    TEST,
    LPATH,
    RPATH,
    SHORTEST,
    INVALID,
};


enum ReturnCodes {
    SUCCESS = 0,
    FAIL = 1,
    NUM_VALID,
    NUM_INVALID,
    FILE_PATH_VALID,
    FILE_PATH_INVALID,
};

enum ErrorCodes {
    NO_ERROR,
    ERROR_INVALID_FILE_PATH,
    ERROR_INVALID_NUMBER,
};


typedef struct {
    int rows;
    int cols;
    unsigned char * cells;
} Map;

typedef struct {
    int row;
    int col;
} Start;


int getArgVal(const int argc, const char * argv[]);
int isNumeric(const char * str);
int isFileValid(const char * filePath);
void loadParams(const char * argv[]);
void printMap();

int argInvalid();
int argHelp();
int argTest();
int argLPath();
int argRPath();
int argShortest();

int startBorder(Map *map, int r, int c, int leftright);
bool isBorder(Map *map, int r, int c, int border);


static Map   map = {.rows = 0, .cols = 0, .cells = NULL};
static Start start = {.row = 0, .col = 0};
static int   errorCode = NO_ERROR;


int main(const int argc, const char * argv[])
{
    int argVal = INVALID;
    int retVal = FAIL;

    argVal = getArgVal(argc, argv);

    switch (argVal) {
        case HELP:
            retVal = argHelp();
            break;
        case TEST:
            retVal = argTest();
            break;
        case LPATH:
            retVal = argLPath();
            break;
        case RPATH:
            retVal = argRPath();
            break;
        case SHORTEST:
            retVal = argShortest();
            break;
        default: // invalid
            retVal = argInvalid();
            break;
    }

    printMap();

    return retVal;
}

int getArgVal(int const argc, char const * argv[])
{
    int argVal = INVALID;
    
    switch (argc) {
        case 2:
            if (strcmp(argv[1], "--help") == 0) {argVal = HELP ;}
            break;
        case 3:
            if ((strcmp(argv[1], "--test") == 0) && (isFileValid(argv[3]) == FILE_PATH_VALID)) {argVal = TEST ;}
            break;
        case 5:
            if ((isNumeric(argv[2]) == NUM_VALID) && (isNumeric(argv[3]) == NUM_VALID) && (isFileValid(argv[4]) == FILE_PATH_VALID)) {
                if (strcmp(argv[1], "--rpath")    == 0) {argVal = RPATH    ; loadParams(argv);}
                if (strcmp(argv[1], "--lpath")    == 0) {argVal = LPATH    ; loadParams(argv);}
                if (strcmp(argv[1], "--shortest") == 0) {argVal = SHORTEST ; loadParams(argv);}
            }
            break;
        default:
            argVal = INVALID;
    }

    return argVal;
}

int isNumeric(const char * str)
{
    int retVal = NUM_INVALID;

    if (str == NULL) {
        errorCode = ERROR_INVALID_NUMBER;
    } else {
        char *endptr;
        strtol(str, &endptr, 10);

        // check if the entire string was converted and if the remaining characters are whitespace
        retVal = (*endptr == '\0' || isspace((unsigned char)*endptr)) ? NUM_VALID : NUM_INVALID;
    }

    return retVal;
}

int isFileValid(char const * filePath)
{
    int retVal = FILE_PATH_INVALID;

    FILE * file = fopen(filePath, "r");

    if (file == NULL) {
        errorCode = ERROR_INVALID_FILE_PATH;
    } else {
        fclose(file);
        retVal = FILE_PATH_VALID;
    }

    return retVal;
}

void loadParams(char const * argv[])
{
    start.row = strtol(argv[2], NULL, 10);
    start.col = strtol(argv[3], NULL, 10);

    FILE * file = fopen(argv[4], "r");
    char lineBuf[LINE_BUFFER_SIZE];

    // extract number of rows and cols
    fgets(lineBuf, sizeof(lineBuf), file);
    sscanf(lineBuf, "%d %d", &(map.rows), &(map.cols));

    // allocate enough memmory for all cells
    map.cells = malloc(map.rows*map.cols*sizeof(unsigned char));

    // copy cells from file
    for (int tmpInt = 0, cellsIdx = 0; fscanf(file, "%u", &tmpInt) == 1; cellsIdx++) {
        map.cells[cellsIdx] = (unsigned char)tmpInt;
    }

    fclose(file);
}

void printMap()
{
    printf("rows: %d\n", map.rows);
    printf("cols: %d\n", map.cols);
    printf("cells:\n");
    for (int i = 0; i < map.rows; i++) {
        for (int j = 0; j < map.cols; j++) {
            printf("%c ", map.cells[i*map.cols + j]);
        }
        printf("\n");
    }
}

int argInvalid() {
    return SUCCESS;
}

int argHelp() {
    printf("Program can be used in following use cases:\n");
    printf("#1 ./maze --help : show possible program arguments\n");
    printf("#2 ./maze --test file.txt : tests if file contains valid maze definition, prints \"Valid\" if so and \"Invalid\" otherwise\n");
    printf("#3 ./maze [--rpath | --lpath | --shortest] R C file.txt finds path though maze defined in file.txt with entrance in row R and collumn C,\n");
    printf("   where serch option --rpath finds exit using right hand rule, --lpath left hand rule and --shortest finds shortest path to exit\n");

    return SUCCESS;
}

int argTest() {
    return SUCCESS;
}

int argLPath() {
    return SUCCESS;
}

int argRPath() {
    return SUCCESS;
}

int argShortest() {
    return SUCCESS;
}