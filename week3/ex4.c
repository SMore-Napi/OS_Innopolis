#include <stdio.h>

/**
 * Roman Soldatov BS19-02
 *
 * Exercise 4
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
 * Quick sort algorithm
 * Sort elements in [l; r] range
 */
void quick_sort(int *array, int l, int r);

/**
 * Print array of integers
 */
void print_array(int *array, int size);

int main() {

    int size = 19;
    int array[] = {5, 2, 7, 89, 2, 3, 8, 1, 22, -8, 3, 3, 6, 9, -3, 0, 3, -7, 6};

    printf("Initial array:\n");
    print_array(array, size);

    quick_sort(array, 0, size - 1);

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

void quick_sort(int *array, int l, int r) {
    int li = l;
    int ri = r;
    // Take the pivot as the middle element
    int pivot = array[(li + ri) / 2];

    // Do the partitioning
    do {
        // Find two elements between the pivot to swap.
        // From the left side it must be greater than pivot
        // From the right side it must be less than pivot
        while (pivot > array[li]) {
            li++;
        }
        while (pivot < array[ri]) {
            ri--;
        }

        // Swap two elements if they are between the pivot
        if (li <= ri) {
            swap(&array[li], &array[ri]);
            li++;
            ri--;
        }
    } while (li < ri);

    // Recursively apply the above steps to the sub-array of elements with smaller values
    if (ri > l) {
        quick_sort(array, l, ri);
    }

    // Recursively apply the above steps to the sub-array of elements with greater values
    if (li < r) {
        quick_sort(array, li, r);
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
