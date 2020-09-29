#include <stdio.h>
#include <stdlib.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 2
 */

int main() {
    int n;

    // Program should prompt the user to enter N before allocating the memory.
    printf("Enter N: ");
    scanf("%d", &n);

    // Dynamically allocate memory for an array of N integers
    int *array = malloc(n * sizeof(int));

    // Fill the array with incremental values starting from 0
    for (int i = 0; i < n; i++) {
        *(array + i) = i;
    }

    // Print the array
    printf("Array: [");
    for (int i = 0; i < n - 1; i++) {
        printf("%d, ", array[i]);
    }
    if (n > 0) {
        printf("%d", array[n - 1]);
    }
    printf("]\n");

    // Deallocate the memory
    free(array);

    return 0;
}
