#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // TODO: remove redundant library inclusions
#include <ctype.h>      // size_t variable type
#include <stdbool.h>    // bool variable type


#define DEBUG_ENABLE        0       // flag enabling debug output, 0 ... disabled, 1 ... enabled
#define MAX_ADDR_LEN        101     // number of character + one '\0' terminating character
#define ASCII_CHAR_COUNT    128


void analyze_addresses(const char * prefix_str, const char * address_str);
int  print_solution();


bool ascii_table_flags[ASCII_CHAR_COUNT] = {0};
char perfect_match_str[MAX_ADDR_LEN] = {0};
bool perfect_match_flag = 0;


int main(int argc, char const *argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "ERROR: No argument.\n");
        return 0;
    }

    if (argc >= 4) {
        fprintf(stderr, "ERROR: Too many arguments.\n");
        return 0;
    }

    if (argc == 2) {
        analyze_addresses("", argv[1]);
    } else {
        analyze_addresses(argv[1], argv[2]);
    }

    print_solution();
    
    return 0;
}

void analyze_addresses(const char * pref_str, const char * addr_str) {
    
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

int print_solution() {
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
        printf("Enable:");
        for (size_t i = 0; i < ASCII_CHAR_COUNT; i++) {
            if (ascii_table_flags[i] == 1) {
                printf("%c\n", (char)i);
            }
        }
    }
}