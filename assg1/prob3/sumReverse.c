#include <stdio.h>
// Author: Louis Romeo
// CSC 352
// Assignment 1 Problem 3
// Purpose: Program should read in the input numbers, and for each number
// calculate the sum of reverse as defined above. Your program should print out sumRev
// on separate lines where sumRev is the calculated number.

// Function to reverse a number
int reverse(int num) {
    int rev = 0;
    while (num > 0) {
        rev = rev * 10 + (num % 10);
        num /= 10;
    }
    return rev;
}

// Function to calculate sum of the number and its reverse
int sumReverse(int num) {
    return num + reverse(num);
}

int main() {
    int num;

    // Read input until EOF
    while (scanf("%d", &num) == 1) {
        if (num <= 0) {
            fprintf(stderr, "Error: Non-positive integer encountered\n");
            return 1; // Exit with error if non-positive integer is encountered
        }

        // Calculate the sum of the number and its reverse
        int sum_rev = sumReverse(num);
        printf("%d\n", sum_rev);
    }

    // If scanf encounters a non-integer value
    if (!feof(stdin)) {
        fprintf(stderr, "Error: Invalid input encountered\n");
        return 1;
    }

    return 0;
}
