#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define DEBUG_OUTPUT     0      // enabled ... 1, disabled ... 0
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

enum Orientation {
    LEFT,
    TOP,
    RIGHT,
    BOTTOM,
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

typedef struct {
    int row;
    int col;
    int entered;
} Position;


static int getArgVal(const int argc, const char * argv[]);
static int isNumeric(const char * str);
static int isFileValid(const char * filePath);
static void loadParams(const char * argv[]);
#if DEBUG_OUTPUT
static void printMap();
#endif //DEBUG_OUTPUT

static int argInvalid();
static int argHelp();
static int argTest(const char * argv[]);
static int argLPath();
static int argRPath();
static int argShortest();

static void startBorder();
static void printPos();
static void cleanup();

static void go(int direction);
static bool isEndNear();
static int  getCellIdx(int r, int c);
static bool isBorder(int border);
static bool isBorderCell(int row, int col, int border);
static bool getBit(unsigned char cell, int position);


static Map      map = {.rows = 0, .cols = 0, .cells = NULL};
static Start    start = {.row = 0, .col = 0};
static Position pos = {.row = 0, .col = 0, .entered = TOP};
static int      errorCode = NO_ERROR;


int main(const int argc, const char * argv[])
{
    int argVal = INVALID;
    int retVal = FAIL;

    argVal = getArgVal(argc, argv);

    #if DEBUG_OUTPUT
        printMap();
    #endif

    switch (argVal) {
        case HELP:
            retVal = argHelp();
            break;
        case TEST:
            retVal = argTest(argv);
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

    cleanup();

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
            if ((strcmp(argv[1], "--test") == 0) && (isFileValid(argv[2]) == FILE_PATH_VALID)) {argVal = TEST ;}
            break;
        case 5:
            if ((isNumeric(argv[2]) == NUM_VALID) && (isNumeric(argv[3]) == NUM_VALID) && (isFileValid(argv[4]) == FILE_PATH_VALID)) {
                if (strcmp(argv[1], "--rpath")    == 0) {argVal = RPATH    ; loadParams(argv); startBorder();}
                if (strcmp(argv[1], "--lpath")    == 0) {argVal = LPATH    ; loadParams(argv); startBorder();}
                if (strcmp(argv[1], "--shortest") == 0) {argVal = SHORTEST ; loadParams(argv); startBorder();}
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

#if DEBUG_OUTPUT
void printMap()
{
    printf("rows: %d\n", map.rows);
    printf("cols: %d\n", map.cols);
    printf("cells:\n");
    for (int i = 0; i < map.rows; i++) {
        for (int j = 0; j < map.cols; j++) {
            printf("%d ", map.cells[i*map.cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}
#endif // DEBUG_OUTPUT

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

int argTest(const char * argv[])
{
    bool fileValid = true;

    FILE *file = fopen(argv[2], "r");

    int rowNum;
    int colNum;
    
    int rowCount = 0;
    int colCount = 0;
    
    char lineBuf[100];

    // extract number of rows and cols
    fgets(lineBuf, sizeof(lineBuf), file);
    sscanf(lineBuf, "%d %d", &(rowNum), &(colNum));

    while (fgets(lineBuf, sizeof(lineBuf), file) != NULL) {
        rowCount++;
        colCount = 0;

        // tokenize the line
        char *token = strtok((char *)lineBuf, " \t");

        while (token != NULL) {
            strtol(token, NULL, 10);
            colCount++;
            token = strtok(NULL, " \t");
        }
        if (colCount != colNum) {
            fileValid = false;
        }
    }

    if (rowCount != rowNum) {
        fileValid = false;
    }

    fclose(file);

    if (fileValid == true) {
        FILE * file = fopen(argv[2], "r");
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

        // test if neighbor cells have matching borders
        for (int row = 1; row < map.rows; row++) {
            for (int col = 1; col < map.cols; col++) {
                if (!(col - 1 < 1)) {
                    if (!(isBorderCell(row, col, LEFT) == isBorderCell(row, col - 1, RIGHT))) {
                        fileValid = false;
                    }
                }

                if (!(col + 1 > map.cols)) {
                    if (!(isBorderCell(row, col, RIGHT) == isBorderCell(row, col + 1, LEFT))) {
                        fileValid = false;
                    }
                }

                if (!(row - 1 < 1)) {
                    if (!(isBorderCell(row, col, TOP) == isBorderCell(row - 1, col, BOTTOM))) {
                        fileValid = false;
                    }
                }

                if (!(row + 1 > map.cols)) {
                    if (!(isBorderCell(row, col, BOTTOM) == isBorderCell(row + 1, col, TOP))) {
                        fileValid = false;
                    }
                }
            }
        }
    }


    if (fileValid == true) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return SUCCESS;
}

int argLPath()
{
    bool endIsNear = false;
    bool moved     = false;
    while (!endIsNear) {
        printPos();
        moved = false;
        while (!moved) {
            if (pos.entered == LEFT) {
                if(!isBorder(TOP)) {
                    go(TOP);
                    moved = true;
                } else {
                    pos.entered = TOP;
                }
            } else if (pos.entered == TOP) {
                if(!isBorder(RIGHT)) {
                    go(RIGHT);
                    moved = true;
                } else {
                    pos.entered = RIGHT;
                }
            } else if (pos.entered == RIGHT) {
                if(!isBorder(BOTTOM)) {
                    go(BOTTOM);
                    moved = true;
                } else {
                    pos.entered = BOTTOM;
                }
            } else if (pos.entered == BOTTOM) {
                if(!isBorder(LEFT)) {
                    go(LEFT);
                    moved = true;
                } else {
                    pos.entered = LEFT;
                }
            }
        }
        endIsNear = isEndNear();
    }
    return SUCCESS;
}

int argRPath() {
    bool endIsNear = false;
    bool moved     = false;
    while (!endIsNear) {
        printPos();
        moved = false;
        while (!moved) {
            if (pos.entered == LEFT) {
                if(!isBorder(BOTTOM)) {
                    go(BOTTOM);
                    moved = true;
                } else {
                    pos.entered = BOTTOM;
                }
            } else if (pos.entered == TOP) {
                if(!isBorder(LEFT)) {
                    go(LEFT);
                    moved = true;
                } else {
                    pos.entered = LEFT;
                }
            } else if (pos.entered == RIGHT) {
                if(!isBorder(TOP)) {
                    go(TOP);
                    moved = true;
                } else {
                    pos.entered = TOP;
                }
            } else if (pos.entered == BOTTOM) {
                if(!isBorder(RIGHT)) {
                    go(RIGHT);
                    moved = true;
                } else {
                    pos.entered = RIGHT;
                }
            }
        }
        endIsNear = isEndNear();
    }
    return SUCCESS;
}

int argShortest() {
    return SUCCESS;
}

void startBorder()
{
    pos.row = start.row;
    pos.col = start.col;
         if (start.row == 1        && start.col == 1        ) { 
            if(!isBorder(TOP))    {pos.entered = TOP  ;}
            if(!isBorder(LEFT))   {pos.entered = LEFT ;}}
    else if (start.row == 1        && start.col == map.cols ) {
            if(!isBorder(TOP))    {pos.entered = TOP   ;}
            if(!isBorder(RIGHT))  {pos.entered = RIGHT ;}}
    else if (start.row == map.rows && start.col == 1        ) {
            if(!isBorder(LEFT))   {pos.entered = LEFT   ;}
            if(!isBorder(BOTTOM)) {pos.entered = BOTTOM ;}}
    else if (start.row == map.rows && start.col == map.cols ) {
            if(!isBorder(RIGHT))  {pos.entered = RIGHT  ;}
            if(!isBorder(BOTTOM)) {pos.entered = BOTTOM ;}}
    else if (start.row == 0        ) {pos.entered = TOP    ;}
    else if (start.row == map.rows ) {pos.entered = BOTTOM ;}
    else if (start.col == 0        ) {pos.entered = LEFT   ;}
    else if (start.col == map.cols ) {pos.entered = RIGHT  ;}
}

void printPos()
{
    printf("%d,%d", pos.row, pos.col);

    #if DEBUG_OUTPUT
        printf(", ");
        switch (pos.entered) {
            case LEFT:
                printf("left");
                break;
            case TOP:
                printf("top");
                break;
            case RIGHT:
                printf("right");
                break;
            case BOTTOM:
                printf("bot");
                break;
            default:
                break;
        }
    #endif

    printf("\n");
}

static void cleanup()
{
    if (map.cells != NULL) {
        free(map.cells);
    }
}

static void go(int direction)
{
    if (direction == TOP) {
        pos.row--;
        pos.entered = BOTTOM;
    } else if (direction == BOTTOM) {
        pos.row++;
        pos.entered = TOP;
    } else if (direction == LEFT) {
        pos.col--;
        pos.entered = RIGHT;
    } else if (direction == RIGHT) {
        pos.col++;
        pos.entered = LEFT;
    }
}

static bool isEndNear()
{
    bool retVal = false;
    if ((pos.row < 1) || (pos.row > map.rows) || (pos.col < 1) || (pos.col > map.cols)) {
        retVal = true;
    }
    return retVal;
}

int getCellIdx(int row, int col)
{
    return ((row-1)*map.cols + (col-1));
}

bool isBorder(int border)
{
    bool retVal = false;

    switch (border) {
        case TOP:
            if ((getBit(map.cells[getCellIdx(pos.row, pos.col)], 2)) || ((pos.row + pos.col) % 2 == 1)) {
                retVal = true;
            }
            break;
        case BOTTOM:
            if ((getBit(map.cells[getCellIdx(pos.row, pos.col)], 2)) || ((pos.row + pos.col) % 2 == 0)) {
                retVal = true;
            }
            break;
        case LEFT:
            if (getBit(map.cells[getCellIdx(pos.row, pos.col)], 0)) {
                retVal = true;
            }
            break;
        case RIGHT:
            if (getBit(map.cells[getCellIdx(pos.row, pos.col)], 1)) {
                retVal = true;
            }
            break;
        default:
            break;
    }

    return retVal;
}

bool isBorderCell(int row, int col, int border)
{
    bool retVal = false;

    switch (border) {
        case TOP: 
            if ((getBit(map.cells[getCellIdx(row, col)], 2)) || ((row + col) % 2 == 1)) {
                retVal = true;
            }
            break;
        case BOTTOM:
            if ((getBit(map.cells[getCellIdx(row, col)], 2)) || ((row + col) % 2 == 0)) {
                retVal = true;
            }
            break;
        case LEFT:
            if (getBit(map.cells[getCellIdx(row, col)], 0)) {
                retVal = true;
            }
            break;
        case RIGHT:
            if (getBit(map.cells[getCellIdx(row, col)], 1)) {
                retVal = true;
            }
            break;
        default:
            break;
    }

    return retVal;
}

bool getBit(unsigned char cell, int position) {
    return (cell >> position) & 1;
}