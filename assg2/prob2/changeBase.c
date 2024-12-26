#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 7 // 6 characters + null terminator

// Author: Louis Romeo
// CSC 352
// Assignment 2 Problem 2
// Purpose: Program that will read in a base, followed by a series of white space separated
// strings that represent numbers in that base. For each of these strings, convert it into
// an unsigned long and print the value out using printf(“%lu\n”).

// Function to convert a character to its numerical value
int char_to_value(char c) {
    if (isdigit(c)) {
        return c - '0'; // Converts '0' to 0 etc.
    } else if (isalpha(c)) {
        return tolower(c) - 'a' + 10; // 'a' -> 10 ... 'z' -> 35
    }
    return -1; // Invalid character
}

// Function to check if the string is valid for the given base
int is_valid_base_string(const char *str, int base) {
    for (int i = 0; str[i]; i++) {
        int value = char_to_value(str[i]);
        if (value == -1 || value >= base) {
            return 0; // Invalid character or out-of-range value for the base
        }
    }
    return 1;
}

// Converts a string in a given base to an unsigned long (Horner's rule)
unsigned long convert_to_ulong(const char *str, int base) {
    unsigned long result = 0;
    for (int i = 0; str[i]; i++) {
        result = result * base + char_to_value(str[i]);
    }
    return result;
}

int main() {
    int base;
    char input_string[MAX_LEN];

    if (scanf("%d", &base) != 1 || base < 2 || base > 36) { // Read the base
        fprintf(stderr, "Error: Base must be between 2 and 36\n");
        return 1;
    }

    // Read and process base numbers one at a time
    while (scanf("%6s", input_string) == 1) {
        // Check if the string is valid for the given base
        if (!is_valid_base_string(input_string, base)) {
            fprintf(stderr, "Error: Invalid number for base %d: %s\n", base, input_string);
            continue;
        }

        // Convert the valid string to an unsigned long and print it
        unsigned long result = convert_to_ulong(input_string, base);
        printf("%lu\n", result); // The “%lu” is the code for unsigned long
    }

    return 0;
}
