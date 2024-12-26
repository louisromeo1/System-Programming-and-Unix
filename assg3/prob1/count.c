/*
* File: count.c
* Author: Louis Romeo
* Purpose: Reads in a sequence of integers and counts the number
* of times each integer value appears in the sequence.
*/
#include <stdio.h>
#include <stdlib.h>

/*
* compare(*a, *b) -- Function to compare two integers
* (for sorting)
*/
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;

    // Read the first integer
    // indicates how many numbers
    if (scanf("%d", &N) != 1 || N <= 0) {
        fprintf(stderr, "Error: Invalid input for N\n");
        return 1;
    }

    // Dynamically allocate memory for N integers
    int *numbers = (int *)malloc(N * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    // Read N integers from input
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Error: Could not read enough integers\n");
            free(numbers);
            return 1;
        }
    }

    // Sort
    qsort(numbers, N, sizeof(int), compare);

    // Count and print the occurrences of each distinct number
    int current_value = numbers[0];
    int count = 1;

    for (int i = 1; i < N; i++) {
        if (numbers[i] == current_value) {
            count++;
        } else {
            printf("%d %d\n", current_value, count);
            current_value = numbers[i];
            count = 1;
        }
    }

    // Print the last value and its count
    printf("%d %d\n", current_value, count);

    // Free the dynamically allocated memory
    free(numbers);

    return 0;
}
