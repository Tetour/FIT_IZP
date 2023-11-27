#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


enum Args {
    HELP = 0,
    TEST,
    LPATH,
    RPATH,
    SHORTEST,
    INVALID,
};

enum MainReturn {
    SUCCESS = 0,
    FAIL,
};

enum IsNumReturn {
    NUM_VALID = 0,
    NUM_INVALID,
};

enum ISFileValid {
    FILE_VALID = 0,
    FILE_INVALID,
};

typedef struct {
    int rows;
    int cols;
    unsigned char *cells;
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


static Map   map;
static Start start;


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
            if (strcmp(argv[1], "--test") == 0) {argVal = TEST ;}
            break;
        case 5:
            if ((isNumeric(argv[2]) == NUM_VALID) && (isNumeric(argv[3]) == NUM_VALID) && (isFileValid(argv[4]) == FILE_VALID)) {
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

    if (!(str == NULL)) {

        char *endptr;
        strtol(str, &endptr, 10);

        // check if the entire string was converted and if the remaining characters are whitespace
        retVal = (*endptr == '\0' || isspace((unsigned char)*endptr)) ? NUM_VALID : NUM_INVALID;
    }

    return retVal;
}

int isFileValid(char const * filePath)
{
    int retVal = FAIL;

    FILE * file = fopen(filePath, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filePath);
        return 1;  // Return an error code
    }

    // Read and print the contents of the file line by line
    char buffer[1024];  // A buffer to store read data
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Line: %s", buffer);
    }

    fclose(file);

    return SUCCESS;
}

void loadParams(char const * argv[])
{
    start.row = strtol(argv[2], NULL, 10);
    start.col = strtol(argv[3], NULL, 10);


}

void printMap()
{

}

int argInvalid() {
    return SUCCESS;
}

int argHelp() {
    printf("Program can be used in following use cases:");
    printf("./maze --help : show possible program arguments");
    printf("./maze --test file.txt : tests if file contains valid maze definition, prints \"Valid\" if so and \"Invalid\" otherwise");
    printf("./maze [--rpath | --lpath | --shortest] R C file.txt finds path though maze defined in file.txt with entrance in row R and collumn C");
    printf("\tserch option --rpath finds exit using right hand rule, --lpath left hand rule and --shortest finds shortest path to exit");

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