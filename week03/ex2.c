#include <stdio.h>

/**
 * Roman Soldatov BS19-02
 *
 * Exercise 2
 */

/**
 * Function declarations
 */

/**
 * Swap two elements.
 * Took from lab2.
 */
void swap(int *a, int *b);

/**
 * Bubble sort algorithm
 */
void bubble_sort(int *array, int size);

/**
 * Print array of integers
 */
void print_array(int *array, int size);


int main() {

    int size = 19;
    int array[] = {5, 2, 7, 89, 2, 3, 8, 1, 22, -8, 3, 3, 6, 9, -3, 0, 3, -7, 6};

    printf("Initial array:\n");
    print_array(array, size);

    bubble_sort(array, size);

    printf("Sorted array:\n");
    print_array(array, size);

    return 0;
}

/**
 * Function implementations
 */

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * This function accepts an array of integers and sort it in place
 */
void bubble_sort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (array[j + 1] < array[j]) {
                swap(&array[j + 1], &array[j]);
            }
        }
    }
}

void print_array(int *array, int size) {
    printf("[");
    for (int i = 0; i < size - 1; ++i) {
        printf("%d, ", array[i]);
    }
    if (size > 0) {
        printf("%d", array[size - 1]);
    }
    printf("]\n");
}
