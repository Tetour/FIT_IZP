#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("ERROR: incorrect number of arguments\n");
        return 1;
    }

    int posun = atoi(argv[1]);
    char encoded_str[100] = {0};
    int i = 0;
    char c = argv[2][i];

    while (c != '\0') {
        if (c >= 'A' && c <= 'Z') {
            if (c + posun > 'Z') {
                encoded_str[i] = c + posun - 26;
            } else {
                encoded_str[i] = c + posun;
            }
        } else if (c >= 'a' && c <= 'z') {
            if (c + posun > 'z') {
                encoded_str[i] = c + posun - 26;
            } else {
                encoded_str[i] = c + posun;
            }
        } else {
            encoded_str[i] = c;
        }

        i++;
        c = argv[2][i];
    }

    printf("%s\n", encoded_str);
     

    return 0;
}

