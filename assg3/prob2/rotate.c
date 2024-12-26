/*
* File: rotate.c
* Author: Louis Romeo
* Purpose: Rotates a vector of integers as specified and
* prints out the rotated vector
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, R;

    // Read the size of the vector
    if (scanf("%d", &N) != 1 || N <= 0) {
        fprintf(stderr, "Error: Invalid input for N\n");
        return 1;
    }

    // Dynamically allocate memory
    int *vector = (int *)malloc(N * sizeof(int));
    if (vector == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    // Read the vector elements
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &vector[i]) != 1) {
            fprintf(stderr, "Error: Could not read enough integers\n");
            free(vector);
            return 1;
        }
    }

    // Read the rotation value
    if (scanf("%d", &R) != 1) {
        fprintf(stderr, "Error: Invalid input for R\n");
        free(vector);
        return 1;
    }

    // R to be within the range [0, N)
    R = R % N;
    if (R < 0) {
        R += N;  // Negative rotation
    }

    // Create a new array to store the rotated vector
    int *rotated = (int *)malloc(N * sizeof(int));
    if (rotated == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(vector);
        return 1;
    }

    // Rotation
    // R steps to the right
    for (int i = 0; i < N; i++) {
        rotated[i] = vector[(i + N - R) % N];
    }

    // Print the rotated vector
    for (int i = 0; i < N; i++) {
        printf("%d ", rotated[i]);
    }
    printf("\n");

    // Free the dynamically allocated memory
    free(vector);
    free(rotated);

    return 0;
}
