#include <pthread.h>
#include <stdio.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 3. Prevent the Race Condition
 */

/**
 * This implementation protects us from the race condition,
 * i.e. it guards the shared data (the buffer in this case).
 * For this purpose I used standard mutex and condition variable to lock the critical region
 */

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int buff_index = 0;
int count = 0;
int item_number = 0;

// Use these variables to prevent the race condition
pthread_mutex_t mutex;
pthread_cond_t cond;

void *produce() {
    while (1) {
        // Lock mutex
        pthread_mutex_lock(&mutex);

        // The producer waits for the consumer when it empties the buffer
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("Producer is working... \n");
        fflush(stdout);

        // Add a new item into the buffer
        buffer[buff_index] = item_number++;
        printf("Produce: %d\n", buffer[buff_index]);
        fflush(stdout);
        if (buff_index + 1 < BUFFER_SIZE) {
            buff_index++;
        }
        count++;

        // Release lock
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
}

void *consume() {
    while (1) {
        // Lock mutex
        pthread_mutex_lock(&mutex);

        // The consumer waits for the producer when it fills the buffer
        while (count == 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("Consumer is working... \n");
        fflush(stdout);

        // Read the element from a buffer
        printf("Consume: %d\n", buffer[buff_index]);
        fflush(stdout);
        if (buff_index - 1 > 0) {
            buff_index--;
        }
        count--;

        // Release lock
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char *argv[]) {

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);
    // Initialize cond
    pthread_cond_init(&cond, NULL);

    // Create and launch producer and consumer threads
    pthread_t consumer, producer;
    pthread_create(&consumer, NULL, consume, NULL);
    pthread_create(&producer, NULL, produce, NULL);
    pthread_join(consumer, NULL);
    pthread_join(producer, NULL);

    // Erase
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}