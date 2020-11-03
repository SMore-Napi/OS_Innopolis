#include <stdio.h>

#define RANDOM_FILE "/dev/random"
#define OUTPUT_FILE "ex1.txt"

/**
 * Roman Soldatov BS19-02
 * Exercise 1
 */

int main() {
    // Open /dev/random file
    FILE *dev_random_file = fopen(RANDOM_FILE, "r");
    // Copy 20 characters from /dev/random to the buffer
    char buffer[20];
    fscanf(dev_random_file, "%20s", buffer);
    fclose(dev_random_file);

    // Open ex1.txt file
    FILE *output = fopen(OUTPUT_FILE, "w");
    // Save the output to the file
    fprintf(output, "%20s", buffer);
    fclose(output);

    return 0;
}
