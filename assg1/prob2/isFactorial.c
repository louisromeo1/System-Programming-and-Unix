#include <stdio.h>
// Author: Louis Romeo
// CSC 352
// Assignment 1 Problem 1
// Purpose: The program reads in a sequence of 0 or more positive integer
// values from stdin until no more can be read in; and for each value N so read, prints out
// "N = b!" if there an integer b so that N = b!, and "N not factorial" if no such b

// Function to check if N is a factorial
int isFactorial(int N) {
    int fact = 1;
    int i = 1;

    while (fact < N) {
        i++;
        fact *= i;
    }

    if (fact == N) {
        return i;  // Return the value of b where N = b!
    } else {
        return -1;  // Return -1 if N is not a factorial
    }
}

int main() {
    int N;

    // Read input until EOF
    while (scanf("%d", &N) == 1) {
        if (N <= 0) {
            fprintf(stderr, "Error: Non-positive integer encountered\n");
            return 1; // Exit with error if non-positive integer is encountered
        }

        int result = isFactorial(N);

        if (result != -1) {
            printf("%d = %d!\n", N, result);
        } else {
            printf("%d not factorial\n", N);
        }
    }

    // If the input contains something that cannot be read as an integer
    if (!feof(stdin)) {
        fprintf(stderr, "Error: Invalid input encountered\n");
        return 1;
    }

    return 0;
}
