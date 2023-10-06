#include <stdio.h>
#include <stdlib.h>

int main (){

    // 1) hello world
    // printf("Hello world!\n");

    // 2) vypocet discriminantu
    // int a = 2, b = 12, c = 8, D;
    // printf("diskriminant je %d\n", D);

    // 3) detekce sudosti
    // if (D % 2 == 0) {
    //     printf("diskriminant je sudy\n");
    // } else {
    //     printf("diskriminant je lichy\n");
    // }

    // 4) cislo v intervalu <0, 10>
    // int cislo1;
    // printf("napis cislo ");
    // scanf("%d", &cislo1);
    // if ((cislo1 >= 0) && (cislo1 <= 10)) {
    //     printf("cislo je v intervalu <0, 10>\n");
    // } else {
    //     printf("cislo neni v intervalu <0, 10>\n");
    // }

    // 5) detekce prestupneho roku
    // int rok;
    // printf("napis cislo roku ");
    // scanf("%d", &rok);
    // if ((rok % 4 == 0) && ((rok % 100 != 0) || (rok % 400 == 0))) {
    //     printf("rok je prestupny\n");
    // } else {
    //     printf("rok neni prestupny\n");
    //     return 1;
    // }

    // 6) maximum z 3 cisel
    int a, b, c;

    printf("napis 3 cisla:\n");
    scanf("%d %d %d", &a, &b, &c);
    
    int max = a;

    if (max < b) {
        max = b;
    }

    if (max < a) {
        max = a;
    }

    printf("maximalni cislo je: %d\n", max);

    return 0;
}