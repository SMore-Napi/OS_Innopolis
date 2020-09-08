#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>

// Maximum size of a command
#define BUFFER 256
// The keyword to finish input commands in a shell
#define EXIT "exit\n"

/**
 * Roman Soldatov BS19-02
 * Exercise 4
 */

int main() {

    char command[BUFFER];
    int run = 1;

    while (run) {
        printf("> ");
        fgets(command, sizeof(command), stdin);

        if (strcmp(command, EXIT) == 0) {
            run = 0;
        } else {
            // Continue read commands in a parent process
            // Execute the command in a child process
            int pid = fork();
            if (pid == 0) {
                system(command);
                break;
            }
        }
    }

    return 0;
}
