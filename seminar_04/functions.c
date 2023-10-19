#include <stdio.h>
#include <stdlib.h>

#include "functions.h"


int main()
{
    char name[15], surname[15];

    printf("Write down you name and surname:");
    scanf("%s %s", name, surname);

    if (strIsOnlyLetters(name)) {
        printf("Name string contains only letters.\n");
    } else {
        printf("Name string contains other stuff.\n");
    }

    if (strIsOnlyLetters(surname)) {
        printf("Surname string contains only letters.\n");
    } else {
        printf("Surname string contains other stuff.\n");
    }

    printf("Name have %d characters.\n", strLength(name));

    char chahar = 'a';
    if (findCharPos(chahar, name) == -1) {
        printf("Name does not contain letter %c\n", chahar);
    } else {
        printf("First occurence of \'%c\' is at index %d\n", chahar, findCharPos(chahar, name));
    }

    printf("Number of similar characters in name and surname is %d\n", compareStr(name, surname));

    return 0;
}

int isLetter(char c)
{
    int retVal = 0;

    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        retVal = 1;
    } else {
        retVal = 0;
    }

    return retVal;
}


int strIsOnlyLetters(char * str)
{
    int retVal = 1;
    int i = 0;

    while (str[i] != '\0') {
        if (!isLetter(str[i])) {
            retVal = 0;
        }
        i++;
    }
    
    return retVal;
}

int strLength(char * str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }

    return i;    
}

int findCharPos(char c, char * str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (c == str[i]) {
            return i;
        }
        i++;
    }

    return -1;
}

int compareStr(char * str1, char * str2)
{
    int i = 0;
    int j = 0;
    int count = 0;

    while (str1[i] != '\0') {
        int duplicate = 0;
        for (int k = 0; k < i; i++) {
            if (str1[i] == str1[k]) {
                duplicate = 1;
            }
        }

        if (duplicate) {
            continue;
        }

        while (str2[j] != '\0') {
            if (str1[i] == str2[i]) {
                count++;
                break;
            }
            j++;
        }
        i++;
    }

    return count;
}
