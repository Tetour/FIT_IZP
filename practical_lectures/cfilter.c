#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "ERROR: not enough arguments\n");
        return 0;
    }

    if (argc > 2) {
        fprintf(stderr, "ERROR: too many arguments\n");
        return 0;
    }

    printf("Write chracter to be filtered: ");
    const char c = getchar();

    size_t input_len = strlen(argv[1]);
    for (size_t i = 0; i < input_len; i++) {
        if (c != argv[1][i]) {
            putchar(argv[1][i]);
        }
    }
    printf("\n");
 
    return 0;
}
