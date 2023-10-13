#include <stdio.h>


#define MAX_STR_LEN 101     // number of chars +1 for '\0' end of string


int main()
{
    char str[MAX_STR_LEN] = {0};
    char c;
    size_t str_len = 0;
    size_t str_num_num = 0;
    size_t str_alpha_num = 0;
    size_t i = 0;

    printf("Write down string: ");
    scanf("%s", str);

    i = 0;
    while (str[i] != '\0') {
        i++;
    }

    str_len = i;

    printf("Number of chars in string: %ld\n", str_len);

    c = 'f';
    i = 0;
    while (str[i] != '\0') {
        if (str[i] == c) {
            str[i] = '-';
        }
        i++;
    }

    printf("String with substitution: %s\n", str);
    
    // input with getchar, EOF = ctrl+z on linux
    while (getchar() != EOF) {

    }

    return 0;
}
