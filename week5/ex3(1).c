#include <pthread.h>
#include <stdio.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 3
 */

/**
 * This implementation does not protect us from the race condition,
 * i.e. it does not guard the shared data (the buffer in this case).
 * I implemented my own condition variables and routines for them.
 * The producer takes the value from 'item_number' and increment it.
 * So, we can track on which iteration it stops produce because of the race condition.
 * After each iteration consumer and producer calls the 'check_race_condition' method to check
 * if the buffer index is still in a possible range and both threads don't sleep at the same time.
 *
 * The fatal race condition happens differently.
 * I launched this program several times and the race condition happened on
 * 49-th, 62-nd, 104-th, 879-th, 354-th, 929-th, 1823-rd iteration.
 */

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int buff_index = 0;
int count = 0;
int error = 0;
int item_number = 0;

// For implementing my own sleep and wakeup routines I implemented my condition variables
int producer_cond = 1;
int consumer_cond = 0;

int is_producer_ready() {
    return producer_cond;
}

void producer_sleep() {
    printf("Producer is sleeping.\n");
    fflush(stdout);
    producer_cond = 0;
}

void producer_wakeup() {
    printf("Producer woke up.\n");
    fflush(stdout);
    producer_cond = 1;
}

int is_consumer_ready() {
    return consumer_cond;
}

void consumer_sleep() {
    printf("Customer is sleeping.\n");
    fflush(stdout);
    consumer_cond = 0;
}

void consumer_wakeup() {
    printf("Customer woke up.\n");
    fflush(stdout);
    consumer_cond = 1;
}

/**
 * This method checks when the program should stop if a race condition happened
 */
void check_race_condition() {
    if (buff_index < 0) {
        printf("Race condition happened: buff_index < 0!\n");
        fflush(stdout);
        error = 1;
    } else if (buff_index > BUFFER_SIZE) {
        printf("Race condition happened: buff_index > BUFFER_SIZE!\n");
        fflush(stdout);
        error = 1;
    } else if (consumer_cond == 0 && producer_cond == 0) {
        printf("Race condition happened: both are sleeping!\n");
        fflush(stdout);
        error = 1;
    }
}

void *produce() {
    while (1) {
        // Check if we need to stop this thread (race condition happened)
        if (error) {
            pthread_exit(NULL);
        }

        // If the producer is awake
        if (is_producer_ready()) {
            // Check if we need to stop this thread (race condition happened)
            if (error) {
                pthread_exit(NULL);
            }

            // The producer goes to sleep when it fills the buffer
            if (count == BUFFER_SIZE) {
                producer_sleep();
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

            // Test to see if the consumer should be awakened
            if (count == 1) {
                consumer_wakeup();
            }

            // Check if something went wrong
            check_race_condition();
        }
    }
}

void *consume() {
    while (1) {
        // Check if we need to stop this thread (race condition happened)
        if (error) {
            pthread_exit(NULL);
        }

        // If the consumer is awake
        if (is_consumer_ready()) {
            // Check if we need to stop this thread (race condition happened)
            if (error) {
                pthread_exit(NULL);
            }

            // The consumer goes to sleep when it empties the buffer
            if (count == 0) {
                consumer_sleep();
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

            // Test to see if the producer should be awakened
            if (count == BUFFER_SIZE - 1) {
                producer_wakeup();
            }

            // Check if something went wrong
            check_race_condition();
        }
    }
}

int main(int argc, char *argv[]) {

    // Create and launch producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, produce, NULL);
    pthread_create(&consumer_thread, NULL, consume, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    return 0;
}
