/*
* File: sumLine.c
* Author: Louis Romeo
* Purpose:
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to skip whitespace and check for errors
int skipWhitespaceAndCheck(char **str) {
    while (isspace(**str)) {
        (*str)++;
    }
    return **str == '\0';
}

int main() {
    char *line = NULL; // init
    size_t len = 0;
    int hasError = 0;

    while (getline(&line, &len, stdin) != -1) {
        char *ptr = line;
        int sum = 0;
        int number;

        // Skip initial whitespace
        if (skipWhitespaceAndCheck(&ptr)) {
            fprintf(stderr, "Error: empty line encountered\n");
            hasError = 1;
            continue;
        }

        int success = 1; // Tracks success of line parsing

        while (*ptr != '\0' && success) {
            if (sscanf(ptr, "%d", &number) == 1) {
                if (number < 0) {
                    fprintf(stderr, "Error: negative integer encountered\n");
                    hasError = 1;
                    success = 0;
                    break;
                }
                sum += number;

                // Move pointer past the current integer
                while (*ptr && !isspace(*ptr)) {
                    ptr++;
                }

                // Skip trailing whitespace
                while (isspace(*ptr)) {
                    ptr++;
                }
            } else {
                fprintf(stderr, "Error: non-integer or invalid input\n");
                hasError = 1;
                success = 0;
                break;
            }
        }

        // If the line was successfully processed, print the sum
        if (success) {
            printf("%d\n", sum);
        }
    }

    free(line);
    return hasError;
}
