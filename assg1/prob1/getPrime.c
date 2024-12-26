#include <stdio.h>
#include <stdlib.h>
// Author: Louis Romeo
// CSC 352
// Assignment 1 Problem 2
// Purpose: The program reads in a positive integer from stdin and prints out the
// smallest prime number that is larger than n

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Function to find the smallest prime greater than n
int nextPrime(int n) {
    int candidate = n + 1;
    while (!isPrime(candidate)) {
        candidate++;
    }
    return candidate;
}

int main() {
    int n;

    // Read input from stdin
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    // Find and print the next prime number
    int next_prime = nextPrime(n);
    printf("%d\n", next_prime);

    return 0;
}
