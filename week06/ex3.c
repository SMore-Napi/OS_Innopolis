#include <stdio.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 3
 */

/**
 * Compare the outputs and provide a description of each case:
 * Well, the output results may be differ because it depends on input.
 * There is no any the universal fastest scheduling algorithm
 * as there are different cases when one will work slower, than another and reversed.
 * So, for my particular cases from test1.txt, test2.txt and test3.txt
 * I got that all scheduling algorithms finished all processes at the same time (total CT).
 * However, the shortest job first algorithm had the minimal average TAT and WT
 * comparing with other algorithms.
 * Again, in other tests it may work slower than FCFS or round-robin algorithms.
 *
 * test1.txt I created by myself, test2.txt and text3.txt were taken from lab examples.
 *
 * Here is the output of average time:
 * 1) Input from test1.txt file
 *
 * FCFS algorithm
 * Average TAT: 13.600000
 * Average WT: 10.733333
 * Total CT: 43
 *
 * Shortest job first algorithm
 * Average TAT: 9.066667
 * Average WT: 6.200000
 * Total CT: 43
 *
 * Round-robin algorithm
 * Average TAT: 15.000000
 * Average WT: 12.133333
 * Total CT: 43
 *
 *
 * 2) Input from test2.txt file
 *
 * FCFS algorithm
 * Average TAT: 4.714286
 * Average WT: 3.000000
 * Total CT: 24
 *
 * Shortest job first algorithm
 * Average TAT: 4.071429
 * Average WT: 2.357143
 * Total CT: 24
 *
 * Round-robin algorithm
 * Average TAT: 4.571429
 * Average WT: 2.857143
 * Total CT: 24
 *
 *
 * 3) Input from test3.txt file
 *
 * FCFS algorithm
 * Average TAT: 17.500000
 * Average WT: 13.300000
 * Total CT: 42
 *
 * Shortest job first algorithm
 * Average TAT: 12.100000
 * Average WT: 7.900000
 * Total CT: 42
 *
 * Round-robin algorithm
 * Average TAT: 20.600000
 * Average WT: 16.400000
 * Total CT: 42
 */

// Each process contains its metrics
struct Process {
    int arrival_time;
    int burst_time;
    // The completion time for this process
    int completion_time;
    int turn_around_time;
    int waiting_time;
    // Shows how many time is left before this process will finish
    int time_remaining;
};

/**
 * Function declarations
 */

void calculate_round_robin(struct Process *processes, int n, int m);

void calculate_completion_time(struct Process *processes, int n, int m);

int get_minimal_time_arrival(struct Process *processes, int n);

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
    // The first line of a file contains the count 'n' of processes and 'm' quantum
    // Other 'n' lines contain two numbers: arrival time and burst time for the ith process respectively.
    FILE *file;
    file = fopen("test3.txt", "r");

    int n, m;
    fscanf(file, "%d", &n);
    fscanf(file, "%d", &m);

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
        processes[i].time_remaining = burst_time;

        process_number[i] = i;
    }
    fclose(file);

    // Calculate following metrics for the "First come, first served (FCFS)" algorithm:
    // Completion time(CT), Turn around time(TAT), Waiting time(WT)

    // Here, the completion time means the time when the ith process finished its execution.
    // It's the same as the Exit time(ET)
    calculate_round_robin(processes, n, m);

    // Calculate following metrics for the "First come, first served (FCFS)" algorithm:
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
void calculate_round_robin(struct Process *processes, int n, int m) {
    calculate_completion_time(processes, n, m);
    calculate_turn_around_time(processes, n);
    calculate_waiting_time(processes, n);
}

void calculate_completion_time(struct Process *processes, int n, int m) {

    int executed_processes = 0;

    // The current time moment
    int time = 0;

    while (executed_processes < n) {
        // If none process is waiting,
        // then the next execution will start in the nearest time arrival
        int minimal_time_arrival = get_minimal_time_arrival(processes, n);
        if (minimal_time_arrival > time) {
            time = minimal_time_arrival;
        }

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].time_remaining > 0) {
                // If the process is finally executed
                if (processes[i].time_remaining <= m) {
                    // The time moment where this processed is finished
                    time += processes[i].time_remaining;
                    processes[i].completion_time = time;

                    // Denote that this process has finished
                    processes[i].time_remaining = 0;
                    executed_processes++;
                } else {
                    // Execute this process for 'm' time units
                    processes[i].time_remaining -= m;
                    time += m;
                }
            } // Some strange case if the process has burst_time = 0
            else if (processes[i].arrival_time <= time && processes[i].time_remaining == 0 &&
                     processes[i].burst_time == 0) {
                processes[i].completion_time = time;
                executed_processes++;
            }
        }
    }
}

int get_minimal_time_arrival(struct Process *processes, int n) {
    int time = -1;
    for (int i = 0; i < n; i++) {
        if (processes[i].time_remaining > 0 && (processes[i].arrival_time < time || time == -1)) {
            time = processes[i].arrival_time;
        }
    }
    return time;
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
    int max_completion_time = processes[0].completion_time;
    for (int i = 1; i < n; i++) {
        if (processes[i].completion_time > max_completion_time) {
            max_completion_time = processes[i].completion_time;
        }
    }

    int minimal_time_arriving = processes[0].arrival_time;
    for (int i = 1; i < n; i++) {
        if (processes[i].arrival_time < minimal_time_arriving) {
            minimal_time_arriving = processes[i].arrival_time;
        }
    }


    return max_completion_time - minimal_time_arriving;
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
