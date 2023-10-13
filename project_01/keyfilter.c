#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define DEBUG_ENABLE 1  // flag enabling debug output, 0 ... disabled, 1 ... enabled


size_t address_total_count = 0;
size_t address_found_count = 0;
char   address_array[100][100] = {0};
int    enabled_chars[26] = {0};

const char *prefix_string = "";
const char *address_string = "";

void set_address_count(const char *address_string);
void set_address_array(const char *address_string);


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
        printf("Address count: %ld\n", address_total_count);
        printf("Address list:\n%s\n\n", address_string);
    #endif

    set_address_array(address_string);


    return 0;
}

void set_address_count(const char *address_string) {
    if (address_string == NULL) {
        printf("ERROR: Implementation error, wrong argument in set_address_count funtion.\n");
        exit(1);
    }

    if (strlen(address_string) == 0) {
        printf("ERROR: No addresses available.\n");
        exit(1);
    }

    size_t char_index = 0;
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

void set_address_array(const char *address_string){
    if (address_string == NULL) {
        printf("ERROR: Implementation error, wrong argument in set_address_array funtion.\n");
        exit(1);
    }

    size_t address_index_array = 0;
    size_t char_index_string = 0;
    size_t char_index_array = 0;
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

void analyze_one_address(char *address){

    size_t char_index_address = 0;
    size_t char_index_prefix = 0;
    
    char ch = address[char_index_address];
    
    for (size_t i = 0; i < 100; i++) {
        

        if (prefix_string[char_index_prefix] == '\0') {

        } else if (address[char_index_address] == '\0') {

        }

        if (address[char_index_address] != prefix_string[char_index_prefix]) {
            break;
        } 
    }

    
}

