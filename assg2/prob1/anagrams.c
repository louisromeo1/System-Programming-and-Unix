#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 64

// Author: Louis Romeo
// CSC 352
// Assignment 2 Problem 1
// Purpose: Program reads a sequence of strings from stdin until no
// more strings can be read. For each string S so read, if S is an anagram of the first string in
// the input sequence, then S is printed out on stdout according to the format specified

// Function to sort characters in a string
void sort_string(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

// Function to check if two strings are anagrams
int are_anagrams(char str1[], char str2[]) {
    char temp1[MAX_LEN], temp2[MAX_LEN];

    // Copy strings to temporary arrays
    strcpy(temp1, str1);
    strcpy(temp2, str2);

    // Convert both strings to lowercase for case-insensitive comparison
    for (int i = 0; temp1[i]; i++) {
        temp1[i] = tolower(temp1[i]);
    }
    for (int i = 0; temp2[i]; i++) {
        temp2[i] = tolower(temp2[i]);
    }

    // Sort the characters in both strings
    sort_string(temp1);
    sort_string(temp2);

    // Compare the sorted strings
    return strcmp(temp1, temp2) == 0;
}

// Function to check if a string contains only alphabetic characters
int is_alphabetic(const char str[]) {
    for (int i = 0; str[i]; i++) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char first_string[MAX_LEN];
    char input_string[MAX_LEN];

    // Read the first string
    if (scanf("%63s", first_string) != 1) {
        return 0;  // Terminate if no input
    }

    // Check if the first string contains only alphabetic characters
    if (!is_alphabetic(first_string)) {
        fprintf(stderr, "Error: First string contains non-alphabetic characters\n");
        return 1;
    }

    // Print the first string (since it is always an anagram of itself)
    printf("%s\n", first_string);

    // Read and process the rest of the input strings
    while (scanf("%63s", input_string) == 1) {
        // Check if the string contains only alphabetic characters
        if (!is_alphabetic(input_string)) {
            fprintf(stderr, "Error: Ignoring non-alphabetic string: %s\n", input_string);
            continue;
        }

        // Check if the string is an anagram of the first string
        if (are_anagrams(first_string, input_string)) {
            printf("%s\n", input_string);
        }
    }

    return 0;
}
