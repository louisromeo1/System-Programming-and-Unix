#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Author: Louis Romeo
// CSC 352
// Assignment 4
// Purpose: Program designed to replicate the logic of addition and
// 			subtraction arithmetic operations with string types. Produces
//			a string calculator which takes in either "add" or "sub" and
//			two numbers as input and performs the required operations.


// Function to strip newline character from input strings
void strip_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Function to check if a string contains only numeric characters
int is_numeric(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to remove leading zeros from a result string by returning a new string
char* remove_leading_zeros(char *str) {
    while (*str == '0' && *(str + 1) != '\0') {
        str++;
    }
    return strdup(str); // Return a new string with removed leading zeros
}

// Helper function to compare two numeric strings
int compare_strings(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    return strcmp(str1, str2);
}

/*
* add_strings(const char* str1, const char* str2) --
* Function to add two numeric strings
*/
char* add_strings(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int max_len = (len1 > len2 ? len1 : len2) + 1;

    // Allocate memory for result
    // (maximum length of sum + 1 for '\0')
    char *result = (char*) malloc(max_len + 1);
    if (!result) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    int carry = 0, i = len1 - 1, j = len2 - 1, k = max_len;
    result[k--] = '\0';

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? str1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? str2[j--] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result[k--] = (sum % 10) + '0';
    }

    // Remove leading zeros, make a copy, and free original result
    char* clean_result = remove_leading_zeros(result + k + 1);
    free(result);  // Free the original result
    return clean_result;
}

/*
* subtract_strings(const char* str1, const char* str2) --
* Function to subtract two numeric strings (str1 - str2)
* This handles cases where str1 is smaller than str2 and produces a negative result
*/
char* subtract_strings(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int is_negative = 0;

    // Compare the two strings and determine if the result will be negative
    if (compare_strings(str1, str2) < 0) {
        // If str1 < str2, swap them and mark the result as negative
        const char* temp = str1;
        str1 = str2;
        str2 = temp;
        is_negative = 1;
        int temp_len = len1;
        len1 = len2;
        len2 = temp_len;
    }

    // Allocate memory for result
    // (maximum length of difference + 2 for '-' sign, '\0')
    char *result = (char*) malloc(len1 + 2);
    if (!result) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    int borrow = 0, i = len1 - 1, j = len2 - 1, k = len1;
    result[k--] = '\0';

    while (i >= 0 || j >= 0) {
        int digit1 = (i >= 0) ? str1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? str2[j--] - '0' : 0;
        int diff = digit1 - digit2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[k--] = diff + '0';
    }

    // Remove leading zeros, make a copy, and free original result
    char* clean_result = remove_leading_zeros(result + k + 1);
    free(result);  // Free the original result

    // If the result is negative, prepend a minus sign
    if (is_negative) {
        char* negative_result = (char*) malloc(strlen(clean_result) + 2);
        if (!negative_result) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        sprintf(negative_result, "-%s", clean_result);
        free(clean_result);  // Free the clean result
        return negative_result;
    }

    return clean_result;
}

int main() {
    char *op = NULL, *str1 = NULL, *str2 = NULL;
    size_t len = 0;

    // Read the operation
    if (getline(&op, &len, stdin) == -1) {
        fprintf(stderr, "Error reading operation.\n");
        return EXIT_FAILURE;
    }
    strip_newline(op);

    // Read the two strings
    if (getline(&str1, &len, stdin) == -1 || getline(&str2, &len, stdin) == -1) {
        fprintf(stderr, "Error reading numbers.\n");
        return EXIT_FAILURE;
    }
    strip_newline(str1);
    strip_newline(str2);

    // Check for valid operation
    if (strcmp(op, "add") != 0 && strcmp(op, "sub") != 0) {
        fprintf(stderr, "Error: 1st line not equal to 'add' or 'sub'.\n");
        return EXIT_FAILURE;
    }

    // Check for valid numeric strings
    if (!is_numeric(str1) || !is_numeric(str2)) {
        fprintf(stderr, "Error: Non-numeric characters in input.\n");
        return EXIT_FAILURE;
    }

    char* result;
    if (strcmp(op, "add") == 0) {
        result = add_strings(str1, str2);
    } else {
        result = subtract_strings(str1, str2);
    }

    // Output the result
    printf("%s\n", result);

    // Free dynamically allocated memory
    free(op);
    free(str1);
    free(str2);
    free(result);

    return EXIT_SUCCESS;
}
