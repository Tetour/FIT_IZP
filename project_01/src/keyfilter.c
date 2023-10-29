#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>      // size_t variable type
#include <stdbool.h>    // bool variable type

#define MAX_ADDR_LEN        101     // number of character + one '\0' terminating character
#define ASCII_CHAR_COUNT    128


void analyze_char();
void update();
void print_solution();


bool ascii_table_flags[ASCII_CHAR_COUNT] = {0};
char perfect_match_str[MAX_ADDR_LEN] = {0};

bool perfect_match_flag = 0;
bool end_word_flag = 0;
bool match_flag = 1;

int  pref_i = 0;
int  ch = 'a';
char * pref;


int main(int argc, char * argv[]) {
    if (argc >= 3) {
        fprintf(stderr, "ERROR: Too many arguments.\n");
        exit(0);
    }

    if (argc == 1) {
        pref = "";
    } else {
        pref = argv[1];
    }

    while(ch != EOF) {
        ch = toupper(getchar());

        analyze_char(ch);
        update();
    }

    print_solution();

    return 0;
}

void analyze_char() {
    if (!(ch == pref[pref_i]) &&  (ch == EOF) &&  (match_flag == 1) &&  (pref[pref_i] == '\0'))                     {perfect_match_flag = 1;};
    if (!(ch == pref[pref_i]) && !(ch == EOF) && !(match_flag == 1) &&  (ch == '\n'))                               {end_word_flag = 1;};
    if (!(ch == pref[pref_i]) && !(ch == EOF) && !(match_flag == 1) && !(pref[pref_i] == '\0') &&  (ch == '\n'))    {end_word_flag = 1;};
    if (!(ch == pref[pref_i]) && !(ch == EOF) && !(match_flag == 1) && !(pref[pref_i] == '\0') && !(ch == '\n'))    {match_flag = 0;};
    if (!(ch == pref[pref_i]) && !(ch == EOF) && !(match_flag == 1) &&  (pref[pref_i] == '\0') && !(ch == '\n'))    {ascii_table_flags[ch] = 1;};
    if (!(ch == pref[pref_i]) && !(ch == EOF) && !(match_flag == 1) &&  (pref[pref_i] == '\0') &&  (ch == '\n'))    {perfect_match_flag = 1; end_word_flag = 1;};
}

void update() {
    if (match_flag) {
        pref_i++;
    }

    if (end_word_flag) {
        end_word_flag = 0;
        match_flag = 1;
        pref_i = 0;
    }
}

void print_solution() {
    size_t match_count = 0;
    for (size_t i = 0; i < ASCII_CHAR_COUNT; i++) {
        if (ascii_table_flags[i] == 1) {
            match_count++;
        }
    }

    if (perfect_match_flag == 0 && match_count == 0) {
        printf("Not found\n");
    } else if (perfect_match_flag == 1 && match_count == 0) {
        printf("Found: %s\n", perfect_match_str);
    } else {
        printf("Enable: ");
        for (size_t i = 0; i < ASCII_CHAR_COUNT; i++) {
            if (ascii_table_flags[i] == 1) {
                printf("%c", (char)i);
            }
        }
        printf("\n");
    }
}

/*
void analyze_addresses(char * pref_str, char * addr_str) {

    size_t pref_i = 0;
    size_t addr_i = 0;

    bool reset_pref_i_flag = 0;
    bool prefix_match_flag = 1;

    do {
        if (perfect_match_flag == 0) {
            perfect_match_str[pref_i] = addr_str[addr_i];
        }

        if (pref_str[pref_i] == addr_str[addr_i]) {

            if (prefix_match_flag == 1 && addr_str[addr_i] == '\0') {
                perfect_match_flag = 1;
            } else if (addr_str[addr_i] == '\n') {
                reset_pref_i_flag = 1;
            }

        } else {

            if (prefix_match_flag == 1 && pref_str[pref_i] == '\0') {

                if (addr_str[addr_i] == '\n') {
                    perfect_match_flag = 1;
                    prefix_match_flag = 1;
                    reset_pref_i_flag = 1;
                } else {
                    ascii_table_flags[(size_t)addr_str[addr_i]] = 1;
                    prefix_match_flag = 0;
                }

            } else {

                if (addr_str[addr_i] == '\n') {
                    prefix_match_flag = 1;
                    reset_pref_i_flag = 1;
                } else {
                    prefix_match_flag = 0;
                }
            }
        }

    addr_i++;

    if (reset_pref_i_flag) {
        pref_i = 0;
        reset_pref_i_flag = 0;
    } else {
        pref_i++;
    }

    } while (addr_str[addr_i] != '\0');    bool perfect_match_flag = 0;

    // add string termination to perfect_match_str if needed
    if (perfect_match_flag == 1) {
        size_t i = 0;
        while (perfect_match_str[i] != '\n' && perfect_match_str != '\0') {
            perfect_match_str[i] = toupper(perfect_match_str[i]);
            i++;
        }

        perfect_match_str[i] = '\0';
    }
}
*/