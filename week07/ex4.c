#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include <malloc/malloc.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 4
 */

/**
 * This is my own realloc() function using malloc() and free()
 */
void *my_realloc(void *ptr, size_t size) {
    void *new_ptr;

    // If ptr is NULL, the call is equivalent to malloc(size)
    if (ptr == NULL) {
        new_ptr = malloc(size);
    } // If size is equal to zero, the call is equivalent to free(ptr)
    else if (size == 0) {
        free(ptr);
        return NULL;
    } else {

        new_ptr = malloc(size);
        if (size > malloc_size(ptr)) {
            memcpy(new_ptr, ptr, malloc_size(ptr));
        } else {
            memcpy(new_ptr, ptr, size);
        }

        free(ptr);
    }
    return new_ptr;
}

int main() {

    // Allows user to specify the original array size, stored in variable n1.
    printf("Enter original array size:");
    int n1 = 0;
    scanf("%d", &n1);

    //Create a new array of n1 ints
    int *a1 = malloc(n1 * sizeof(int));
    int i;
    for (i = 0; i < n1; i++) {
        //Set each value in a1 to 100
        *(a1 + i) = i + 1;

        //Print each element out (to make sure things look right)
        printf("%d ", *(a1 + i));
    }

    //User specifies the new array size, stored in variable n2.
    printf("\nEnter new array size: ");
    int n2 = 0;
    scanf("%d", &n2);

    //Dynamically change the array to size n2
    a1 = (int *) my_realloc(a1, n2 * sizeof(int));

    for (i = 0; i < n2; i++) {
        //Print each element out (to make sure things look right)
        printf("%d ", a1[i]);
    }
    printf("\n");

    //Done with array now, done with program :D
    return 0;
}