#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define PATH "ex1.txt"
#define MAX_STRING_SIZE 50
#define NEW_STRING "This is a nice day\n"

/**
 * Roman Soldatov BS19-02
 * Exercise 1
 */

/**
 * Function declarations
 */

void create_file(char *path, int max_string_size);

char *get_random_string(int max_size);

void change_string(char *str);

int main() {

    // Create a file ex1.txt with a random string in it
    create_file(PATH, MAX_STRING_SIZE);

    // Change the string in ex1.txt to “This is a nice day” by using mmap()
    change_string(NEW_STRING);

    return 0;
}

/**
 * Function implementations
 */
void create_file(char *path, int max_string_size) {
    char *random_string = get_random_string(max_string_size);
    FILE *file = fopen(path, "w");
    fprintf(file, "%s\n", random_string);
    fclose(file);
    free(random_string);
}

char *get_random_string(int max_size) {
    srand(time(NULL));
    const char letters[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM 1234567890";
    const int letters_size = strlen(letters);
    int length = rand() % max_size;

    char *random_string = malloc(length * sizeof(char));

    for (int i = 0; i < length; i++) {
        int random_letter = rand() % letters_size;
        random_string[i] = letters[random_letter];
    }
    random_string[length] = '\0';

    return random_string;
}

void change_string(char *str) {
    unsigned long string_size = strlen(str);

    // Open file
    int file = open("ex1.txt", O_RDWR);

    // Get the file size
    struct stat struct_stat;
    fstat(file, &struct_stat);

    // Create a new memory mapping
    char *addr = mmap(NULL, struct_stat.st_size, PROT_WRITE, MAP_SHARED, file, 0);

    // Change the file size
    ftruncate(file, string_size);

    strncpy(addr, str, string_size);
    munmap(addr, string_size);

    close(file);
}