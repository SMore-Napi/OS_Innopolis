#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 2
 */

int main(int argc, char *argv[]) {

    int file_descriptors[argc];
    int count_output_files = 0;

    if (argc >= 2) {

        // Check the -a flag for appending mode
        int flag_append_option;
        if (strcmp(argv[1], "-a") == 0) {
            flag_append_option = 1;
        } else {
            flag_append_option = 0;
        }

        // Read file descriptors from arguments
        if (flag_append_option == 1) {
            for (int i = 2; i < argc; i++) {
                file_descriptors[count_output_files++] = open(argv[i], O_CREAT | O_RDWR | O_APPEND, 0777);
            }
        } else {
            for (int i = 1; i < argc; i++) {
                file_descriptors[count_output_files++] = open(argv[i], O_CREAT | O_RDWR, 0777);
            }
        }
        file_descriptors[count_output_files] = STDOUT_FILENO;
    }

    // Write info to output files
    char character;
    // Read next symbol
    while (read(STDIN_FILENO, &character, 1) > 0) {
        // Write character symbol in each output file
        for (int i = 0; i <= count_output_files; i++) {
            write(file_descriptors[i], &character, 1);
        }
    }

    // Close files
    for (int i = 0; i < count_output_files; i++) {
        close(file_descriptors[i]);
    }
    
    return 0;
}
