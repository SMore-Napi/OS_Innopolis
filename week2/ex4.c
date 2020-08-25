#include <stdio.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 4
 */

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int first, second;
    // Asks user to input two integers
    printf("Input the first integer:\n");
    scanf("%d", &first);

    printf("Input the second integer:\n");
    scanf("%d", &second);


    // Swap integers using a separate function
    swap(&first, &second);

    printf("Do the swapping\n");
    printf("first = %d\n", first);
    printf("second = %d\n", second);

    return 0;
}
