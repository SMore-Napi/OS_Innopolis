#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

/**
 * Roman Soldatov BS19-02
 * Exercise 1
 */

void *run_thread(void *id) {
    // Each thread should output its number and some text
    printf("Thread [%d] is running...\n", (int) id);

    // then exit
    printf("Thread [%d] finished\n", (int) id);
    pthread_exit(NULL);
}

int main() {

    // Array of threads
    pthread_t threads[N];

    int status;
    for (int i = 0; i < N; i++) {

        // Main program should inform about thread creation
        printf("Create thread [%d] in main\n", i);
        status = pthread_create(&threads[i], NULL, run_thread, (void *) i);
        // In case of error.
        if (status != 0) {
            printf("Something went wrong while thread [%d] creation! stutus = %d\n", i, status);
            exit(EXIT_FAILURE);
        }

        // Fix the program to force the order to be strictly
        // thread 1 created, thread 1 prints message, thread 1 exits and so on
        // To fix this problem we can add this line:
        status = pthread_join(threads[i], NULL);
        // In case of error.
        if (status != 0) {
            printf("Something went wrong while thread [%d] joining! stutus = %d\n", i, status);
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
/**
 * The output is not the same each time when we launch this program.
 * The order of creation a thread, running it and exiting is preserved,
 * but this commands can be interrupted by other threads, i.e.
 * threads are not related to each other, they work independently.
 *
 * In case of pthread_join(threads[i], NULL) command  threads will execute sequentially,
 * i.e. in order as they were created.
 */
// Output without joining threads
/*
Create thread [0] in main
Create thread [1] in main
Thread [0] is running...
Thread [0] finished
Create thread [2] in main
Thread [1] is running...
Thread [1] finished
Create thread [3] in main
Create thread [4] in main
Create thread [5] in main
Create thread [6] in main
Thread [2] is running...
Thread [2] finished
Create thread [7] in main
Thread [5] is running...
Thread [5] finished
Create thread [8] in main
Thread [4] is running...
Thread [4] finished
Thread [3] is running...
Thread [3] finished
Thread [6] is running...
Thread [6] finished
Thread [7] is running...
Thread [7] finished
Create thread [9] in main
Thread [8] is running...
Thread [8] finished
Thread [9] is running...
Thread [9] finished
 */
