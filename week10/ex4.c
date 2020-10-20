#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define DIR_PATH "./tmp/"
#define OUTPUT "ex4.txt"
#define SIZE 255

/**
 * Roman Soldatov BS19-02
 * Exercise 4
 */
int main() {
    struct dirent *struct_dirent;
    struct stat struct_stat;

    DIR *dir = opendir(DIR_PATH);
    char name[SIZE];

    FILE *file = fopen(OUTPUT, "w");

    while ((struct_dirent = readdir(dir)) != NULL) {
        snprintf(name, sizeof(name), "%s%s", DIR_PATH, struct_dirent->d_name);
        if (stat(name, &struct_stat) != -1 && struct_stat.st_nlink >= 2) {
            fprintf(file, "%s\n", name);
        }
    }

    fclose(file);

    return 0;
}
