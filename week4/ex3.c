#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum size of a command
#define BUFFER 16
// The keyword to finish input commands in a shell
#define EXIT "exit"

/**
 * Roman Soldatov BS19-02
 * Exercise 3
 */

int main() {

    char command[BUFFER];
    int run = 1;

    while (run) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, EXIT) == 0) {
            run = 0;
        } else {
            system(command);
        }
    }

    return 0;
}
