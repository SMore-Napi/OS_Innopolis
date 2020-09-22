#include <stdio.h>
#include <zconf.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 1
 */

/**
 *  This program accepts an argument n which shows
 *  from each program the current thread prints a message

 * To run this program 10 times I wrote the shell script ex1.sh:
 * for i in {1..10}
 * do
 * 	./ex1 ${i}
 * done
 *
 * This script lunches the program 10 times passing as an argument the number of the iteration

 * Then I compiled this program using this command:
 * gcc ex1.c -o ex1
 *
 * After that, I wrote this command in a terminal to run the shell script:
 * sh ex1.sh
 *
 * The result which I got is below the main
 */

int main(int argc, char *argv[]) {

    int n;
    // In case sscanf has not successfully read
    if (sscanf(argv[1], "%d", &n) != 1) {
        printf("Error argument!");
        return 1;
    }

    int pid = getpid();
    fork();

    if (pid < getpid()) {
        printf("Hello from child [%d - %d]\n", getpid(), n);
    } else {
        printf("Hello from parent [%d - %d]\n", getpid(), n);
    }

    return 0;
}

/**
 * This output can be shuffled. It depends on a system and a hardware
 * because several cores or only one core of the CPU can execute this program.
 * I run this code on a MacBook Pro with 2 cores. Maybe the OS decided to use only one core
 * because another was taken for other runtime programs.
 * That's why it looks like a sequential process, but it's not the rule!
 * There can be the random order of processes.
*/
// Output
/*
Hello from parent [5064 - 1]
Hello from child [5065 - 1]
Hello from parent [5066 - 2]
Hello from child [5067 - 2]
Hello from parent [5068 - 3]
Hello from child [5069 - 3]
Hello from parent [5070 - 4]
Hello from child [5071 - 4]
Hello from parent [5072 - 5]
Hello from child [5073 - 5]
Hello from parent [5074 - 6]
Hello from child [5075 - 6]
Hello from parent [5076 - 7]
Hello from child [5077 - 7]
Hello from parent [5078 - 8]
Hello from child [5079 - 8]
Hello from parent [5080 - 9]
Hello from child [5081 - 9]
Hello from parent [5082 - 10]
Hello from child [5083 - 10]
*/
