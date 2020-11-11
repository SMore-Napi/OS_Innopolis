#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define INPUT_PATH "input.txt"
#define OUTPUT_PATH "output.txt"

/**
 * Roman Soldatov BS19-02
 * Exercise 1
 */

/**
 * Function declarations
 */

void input(int *vector_size, int *processes_number, int **resources_existence, int **resources_available,
           int **current_allocation_matrix, int **request_matrix);

int *read_vector(char *string, int *size);

int *read_matrix(FILE *file, int columns, int rows, int *n);

int get_number_integers_in_string(char *string);

int *reallocate_2d_array(int *old_array, int n, int m);

int *get_terminated_processes(int m, int n, int *a, int *matrixC, const int *matrixR);

void output_result(const int *terminated_processes, int n);

int main() {
    int m; // the number of resource classes
    int n; // the number of processes
    int *e; // existing resource vector
    int *a; // available resource vector
    int *matrixC; // current allocation matrix
    int *matrixR; // request matrix

    // Input variables from a file
    input(&m, &n, &e, &a, &matrixC,
          &matrixR);

    // Determine which processes can be terminated
    int *terminated_processes = get_terminated_processes(m, n, a, matrixC, matrixR);

    // Output the deadlock detection result in a file
    output_result(terminated_processes, n);

    // Free allocated memory
    free(terminated_processes);
    free(e);
    free(a);
    free(matrixC);
    free(matrixR);

    return 0;
}

/**
 * Function implementations
 */
void input(int *vector_size, int *processes_number, int **resources_existence, int **resources_available,
           int **current_allocation_matrix, int **request_matrix) {

    FILE *file = fopen(INPUT_PATH, "r");
    char string[BUFFER_SIZE];

    // Read 'resources in existence' from a file
    fgets(string, BUFFER_SIZE, file);
    // Convert a string to the existing resource vector
    (*resources_existence) = read_vector(string, vector_size);

    // Skip the new line
    fgets(string, BUFFER_SIZE, file);

    // Read 'resources available' from a file
    fgets(string, BUFFER_SIZE, file);
    // Convert a string to the available resource vector
    (*resources_available) = read_vector(string, vector_size);

    // Skip the new line
    fgets(string, BUFFER_SIZE, file);

    // Read the current allocation matrix
    (*current_allocation_matrix) = read_matrix(file, 1024, (*vector_size), processes_number);
    (*current_allocation_matrix) = reallocate_2d_array((*current_allocation_matrix), (*processes_number),
                                                       (*vector_size));

    // Read the request matrix
    (*request_matrix) = read_matrix(file, (*processes_number), (*vector_size), processes_number);

    fclose(file);
}

int *read_vector(char *string, int *size) {

    *size = get_number_integers_in_string(string);
    int *vector = (int *) malloc((*size) * sizeof(int));

    int i = 0;
    char *substring;
    substring = strtok(string, " ");
    while (substring != NULL) {
        vector[i++] = atoi(substring);
        substring = strtok(NULL, " ");
    }

    return vector;
}

int *read_matrix(FILE *file, int columns, int rows, int *n) {

    int *matrix = (int *) malloc(columns * rows * sizeof(int));

    char string[BUFFER_SIZE];
    int m;
    *n = 0;

    fgets(string, BUFFER_SIZE, file);
    while (strcmp(string, "\n")) {
        int *vector = read_vector(string, &m);
        for (int i = 0; i < m; i++) {
            *(matrix + (*n) * m + i) = vector[i];
        }
        (*n)++;
        if (!fgets(string, BUFFER_SIZE, file)) {
            break;
        }
    }

    return matrix;
}

int get_number_integers_in_string(char *string) {
    char copy_string[BUFFER_SIZE];
    strcpy(copy_string, string);

    int counter = 0;
    char *substring = strtok(copy_string, " ");
    while (substring != NULL) {
        counter++;
        substring = strtok(NULL, " ");
    }

    return counter;
}

int *reallocate_2d_array(int *old_array, int n, int m) {
    int *new_array = (int *) malloc(n * m * sizeof(int));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            *(new_array + m * i + j) = *(old_array + m * i + j);
        }
    }
    free(old_array);

    return new_array;
}

int *get_terminated_processes(int m, int n, int *a, int *matrixC, const int *matrixR) {

    // Array of processes. 0 - not terminated process, 1 - terminated process
    int *terminated_processes = (int *) calloc(n, sizeof(int));

    // Do the loop until it is possible to terminate some process
    int run = 1;
    while (run) {
        run = 0;
        // Go to all processes to find out is it possible to terminate so of them
        for (int i = 0; i < n; i++) {
            // In case the current process is not terminated
            if (!terminated_processes[i]) {
                int is_available = 1;
                // Check if granting the request leads to a safe state
                for (int j = 0; j < m; j++) {
                    if (*(matrixR + m * i + j) > a[j]) {
                        is_available = 0;
                        break;
                    }
                }

                // if it is guaranteed to be possible
                // then request all the resources the process needs and finish it
                if (is_available) {
                    for (int j = 0; j < m; j++) {
                        a[j] += *(matrixC + m * i + j);
                        *(matrixC + m * i + j) = 0;
                    }
                    terminated_processes[i] = 1;
                    run = 1;
                }
            }
        }
    }

    return terminated_processes;
}

void output_result(const int *terminated_processes, int n) {
    // Check if at least one process has a deadlock
    int is_deadlocked = 0;
    for (int i = 0; i < n; i++) {
        if (terminated_processes[i] == 0) {
            is_deadlocked = 1;
            break;
        }
    }

    // Print the result
    FILE *file = fopen(OUTPUT_PATH, "w");
    if (!is_deadlocked) {
        fprintf(file, "no deadlock is detected\n");
    } else {
        fprintf(file, "deadlock is detected on processes: ");
        for (int i = 0; i < n; i++) {
            if (terminated_processes[i] == 0) {
                fprintf(file, "%d ", i + 1);
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

