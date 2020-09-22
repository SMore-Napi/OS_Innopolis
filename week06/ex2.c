#include <stdio.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 2
 */

// Each process contains its metrics
struct Process {
    int arrival_time;
    int burst_time;
    // The completion time for this process
    int completion_time;
    int turn_around_time;
    int waiting_time;
};

/**
 * Function declarations
 */

void calculate_SJF(struct Process *processes, int *process_number, int n);

void sort_processes_SJF(struct Process *processes, int *process_number, int n);

int get_minimal_time_arrival(struct Process *processes, int start, int end);

int get_index_shortest_process(struct Process *processes, int time, int start, int end);

void swap_process(struct Process *a, struct Process *b);

void swap_int(int *a, int *b);

void calculate_completion_time(struct Process *processes, int n);

void calculate_turn_around_time(struct Process *processes, int n);

void calculate_waiting_time(struct Process *processes, int n);

double calculate_average_turn_around_time(struct Process *processes, int n);

double calculate_average_waiting_time(struct Process *processes, int n);

int calculate_total_completion_time(struct Process *processes, int n);

void print_process_scheduling(struct Process *processes, int *process_number, int n,
                              double average_turn_around_time, double average_waiting_time,
                              int total_completion_time);

int main() {

    // Read data from a file
    // The first line of a file contains the count 'n' of processes.
    // Other 'n' lines contain two numbers: arrival time and burst time for the ith process respectively.
    FILE *file;
    file = fopen("test2.txt", "r");

    int n;
    fscanf(file, "%d", &n);

    // Array of processes
    struct Process processes[n];
    // Array of indices of processes
    // The order preserves from the input file
    int process_number[n];

    for (int i = 0; i < n; i++) {
        int arrival_time;
        int burst_time;
        fscanf(file, "%d", &arrival_time);
        fscanf(file, "%d", &burst_time);

        processes[i].arrival_time = arrival_time;
        processes[i].burst_time = burst_time;

        process_number[i] = i;
    }
    fclose(file);


    // Calculate following metrics for the "Shortest job first" algorithm:
    // Completion time(CT), Turn around time(TAT), Waiting time(WT)

    // Here, the completion time means the time when the ith process finished its execution.
    // It's the same as the Exit time(ET)
    calculate_SJF(processes, process_number, n);

    // Calculate following metrics for the "Shortest job first" algorithm:
    // Average Turnaround time, Average waiting time, Total completion time
    double average_turn_around_time = calculate_average_turn_around_time(processes, n);
    double average_waiting_time = calculate_average_waiting_time(processes, n);
    // Here, the total completion time means the time when all process finished their executions.
    int total_completion_time = calculate_total_completion_time(processes, n);

    // Output the table of processes metrics
    // The order of processes in the table represents in which order they will execute
    print_process_scheduling(processes, process_number, n,
                             average_turn_around_time, average_waiting_time, total_completion_time);

    return 0;
}

/**
 * Function implementations
 */

void calculate_SJF(struct Process *processes, int *process_number, int n) {
    sort_processes_SJF(processes, process_number, n);
    calculate_completion_time(processes, n);
    calculate_turn_around_time(processes, n);
    calculate_waiting_time(processes, n);
}

void sort_processes_SJF(struct Process *processes, int *process_number, int n) {
    // The current time moment
    int time = 0;
    for (int i = 0; i < n; i++) {
        // If none process is waiting,
        // then the next execution will start in the nearest time arrival
        int minimal_time_arrival = get_minimal_time_arrival(processes, i, n);
        if (minimal_time_arrival > time) {
            time = minimal_time_arrival;
        }

        // Find the shortest process
        int next_process_id = get_index_shortest_process(processes, time, i, n);

        // Move the next shortest process to execute to the beginning of an array (like in the Bubble Sort)
        swap_process(&processes[i], &processes[next_process_id]);
        swap_int(&process_number[i], &process_number[next_process_id]);

        // Next execution will be available on this time:
        time += processes[i].burst_time;
    }
}

int get_minimal_time_arrival(struct Process *processes, int start, int end) {
    int time = processes[start].arrival_time;
    for (int i = (start + 1); i < end; i++) {
        if (processes[i].arrival_time < time) {
            time = processes[i].arrival_time;
        }
    }
    return time;
}

int get_index_shortest_process(struct Process *processes, int time, int start, int end) {
    int min_burst_time = -1;
    int next_process_id = -1;

    for (int j = start; j < end; j++) {
        if (processes[j].arrival_time <= time) {
            if (min_burst_time == -1 || processes[j].burst_time < min_burst_time) {
                next_process_id = j;
                min_burst_time = processes[j].burst_time;
            }
        }
    }

    return next_process_id;
}

void swap_process(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void calculate_completion_time(struct Process *processes, int n) {
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        if (processes[i - 1].completion_time <= processes[i].arrival_time) {
            processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
        } else {
            processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
        }
    }
}

void calculate_turn_around_time(struct Process *processes, int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
    }
}

void calculate_waiting_time(struct Process *processes, int n) {
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
    }
}

double calculate_average_turn_around_time(struct Process *processes, int n) {
    int sum_turn_around_time = 0;
    for (int i = 0; i < n; i++) {
        sum_turn_around_time += processes[i].turn_around_time;
    }

    return (double) sum_turn_around_time / n;
}

double calculate_average_waiting_time(struct Process *processes, int n) {
    int sum_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        sum_waiting_time += processes[i].waiting_time;
    }

    return (double) sum_waiting_time / n;
}

int calculate_total_completion_time(struct Process *processes, int n) {
    return processes[n - 1].completion_time - processes[0].arrival_time;
}

void print_process_scheduling(struct Process *processes, int *process_number, int n,
                              double average_turn_around_time, double average_waiting_time,
                              int total_completion_time) {
    printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process_number[i], processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turn_around_time, processes[i].waiting_time);
    }

    printf("\n");
    printf("Average TAT: %f\n", average_turn_around_time);
    printf("Average WT: %f\n", average_waiting_time);
    printf("Total CT: %d\n", total_completion_time);
}
