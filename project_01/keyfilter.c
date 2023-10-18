#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define DEBUG_ENABLE        1  // flag enabling debug output, 0 ... disabled, 1 ... enabled
#define MAX_ADDRESS_COUNT   100
#define MAX_ADDRESS_LENGTH  100
#define MAX_CHARACTER_COUNT 26
#define ADDRESS_NOT_FOUND   (MAX_ADDRESS_COUNT + 1)


int     address_total_count = 0;
int     address_found_index = ADDRESS_NOT_FOUND;
int     enabled_chars[MAX_CHARACTER_COUNT] = {0};
char    address_array[MAX_ADDRESS_COUNT][MAX_ADDRESS_LENGTH] = {0};

const char *prefix_string = "";
const char *address_string = "";

void set_address_count(const char *address_string);
void set_address_array(const char *address_string);
void analyze_one_address(int address_index);
void print_results();


int main(int argc, char const *argv[])
{
    if (argc <= 1) {
        printf("ERROR: No argument.\n");
        exit(1);
    }

    if (argc >= 4) {
        printf("ERROR: Too many arguments.\n");
        exit(1);
    }

    if (argc == 2) {
        prefix_string  = "";
        address_string = argv[1];
    } else {
        prefix_string  = argv[1];
        address_string = argv[2];
    }

    set_address_count(address_string);

    #if DEBUG_ENABLE
        printf("Input text: %s\n", prefix_string);
        printf("Address count: %d\n", address_total_count);
        printf("Address list:\n%s\n\n", address_string);
    #endif

    set_address_array(address_string);

    for (int i = 0; i < MAX_ADDRESS_COUNT; i++) {
        analyze_one_address(i);
    }

    print_results();

    return 0;
}

void set_address_count(const char *address_string)
{
    if (address_string == NULL) {
        printf("ERROR: Implementation error, wrong argument in set_address_count funtion.\n");
        exit(1);
    }

    if (strlen(address_string) == 0) {
        printf("ERROR: No addresses available.\n");
        exit(1);
    }

    int char_index = 0;
    char ch = address_string[char_index];

    while (ch != '\0') {
        if (ch == '\n') {
            address_total_count++;
        }
        char_index++;
        ch = address_string[char_index];
    }
    address_total_count++;
}

void set_address_array(const char *address_string)
{
    if (address_string == NULL) {
        printf("ERROR: Implementation error, wrong argument in set_address_array funtion.\n");
        exit(1);
    }

    int address_index_array = 0;
    int char_index_string = 0;
    int char_index_array = 0;
    char ch = address_string[char_index_string];

    while (ch != '\0') {
        if (ch == '\n') {
            // TODO: remove redundant assignment
            address_array[address_index_array][char_index_array] = '\0';

            address_index_array++;
            char_index_string++;
            char_index_array = 0;
        }

        address_array[address_index_array][char_index_array] = address_string[char_index_string];
        char_index_string++;
        char_index_array++;
        if (char_index_array >= 100) {
            printf("ERROR: Maximum length of address reached.\n");
            exit(1);
        }
        ch = address_string[char_index_string];

    }
}

void analyze_one_address(int address_index)
{

    const char * address = address_array[address_index];

    if (strcmp(prefix_string, address) == 0) {
        address_found_index = address_index;
    } else {
        if (strncmp(prefix_string, address, strlen(prefix_string)) == 0) {
            char ch = address[strlen(prefix_string) + 1];
            enabled_chars[ch - 'a'] = 1;
            address_found_index = address_index;
        }   
    }
}

void print_results()
{
    char results[MAX_CHARACTER_COUNT * 2] = {0};
    int num_enabled_chars = 0;

    for (int i = 0; i < MAX_CHARACTER_COUNT; i++) {
        if (enabled_chars[i] == 1) {
            num_enabled_chars++;
        }
    }

    if ((num_enabled_chars == 0) && (address_found_index == ADDRESS_NOT_FOUND)) {
        printf("Not found\n");
    } else if (num_enabled_chars == 1) {
        printf("Found: %s\n", address_array[address_found_index]);
    } else if (num_enabled_chars >= 2) {
        int j = 0;
        for (int i = 0; i < MAX_CHARACTER_COUNT; i++) {
            if (enabled_chars[i] == 1) {
                results[j] = (char)(i + 'A');
                j++;
            }
        }
        printf("Enable: %s\n", results);
    } else if ((num_enabled_chars == 0) && (address_found_index != ADDRESS_NOT_FOUND)) {
        printf("Found: %s\n", address_array[address_found_index]);
    }
}