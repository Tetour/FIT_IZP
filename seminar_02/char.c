#include <stdio.h>

int main()
{
    char ch;
    printf("Nacti znak: ");
    scanf("%c", &ch);

    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')){
        printf("znak je pismeno\n");
    } else {
        printf("znak neni pismeno\n");
    }

    if (ch >= 'A' && ch <= 'Z') {
        ch += ('a' - 'A');
    } else if (ch >= 'a' && ch <= 'z') {
        ch -= ('z' - 'Z');
    }

    printf("upraveny znak je %c\n", ch);

    return 0;
}
