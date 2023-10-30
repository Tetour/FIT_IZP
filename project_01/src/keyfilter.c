#include <stdio.h>
#include <string.h>

#define MAX_ADDR_LEN        101     // number of character + one '\0' terminating character
#define ASCII_CHAR_COUNT    128


void get_rid_of_newline(char * str);
void transform_to_upper(char * str);
void print_solution();


int ascii_table_flags[ASCII_CHAR_COUNT] = {0}; // array to store enabled chars as array index

char word[MAX_ADDR_LEN] = {0};
char last_matching_word[MAX_ADDR_LEN] = {0};

char * prefix;


int main(int argc, char * argv[]) {
    if (argc >= 3) {
        fprintf(stderr, "ERROR: Too many arguments.\n");
        return 1;
    }

    if (argc == 1) {
        while (fgets(word, MAX_ADDR_LEN, stdin) != NULL) {
            get_rid_of_newline(word);
            transform_to_upper(word);

            ascii_table_flags[(int)word[0]] = 1;
        }
    } else {
        prefix = argv[1];
        transform_to_upper(prefix);

        while (fgets(word, MAX_ADDR_LEN, stdin) != NULL) {
            get_rid_of_newline(word);
            transform_to_upper(word);

            if (strcmp(prefix, word) == 0) {
                printf("Found: %s\n", word);
                return 0;
            } else {
                int len_pref = strlen(prefix);
                int len_word = strlen(word);
                if (strncmp(prefix, word, len_pref) == 0) {
                    if (len_pref < len_word) {
                        ascii_table_flags[(int)word[len_pref]] = 1;
                        strcpy(last_matching_word, word);
                    }
                }
            }
        }
    }

    print_solution();

    return 0;
}

void get_rid_of_newline(char * str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
        }
    }
}

void transform_to_upper(char * str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if ((str[i] >= 'a') && (str[i] <= 'z')) {
            str[i] = str[i] - 32;
        }
    }
}

void print_solution() {
    int match_count = 0;
    for (int i = 0; i < ASCII_CHAR_COUNT; i++) {
        if (ascii_table_flags[i] == 1) {
            match_count++;
        }
    }

    if (match_count == 0) {
        printf("Not found\n");
    } else if (match_count == 1) {
        printf("Found: %s\n", last_matching_word);
    } else {
        printf("Enable: ");
        for (int i = 0; i < ASCII_CHAR_COUNT; i++) {
            if (ascii_table_flags[i] == 1) {
                printf("%c", (char)i);
            }
        }
        printf("\n");
    }
}
