#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define DIR_PATH "./tmp/"
#define OUTPUT "ex4.txt"
#define CHAR_BUFFER_SIZE 255

/**
 * Roman Soldatov BS19-02
 * Exercise 4
 */

/**
 * Return the number of files in the given directory
 */
int get_number_files_in_directory(char *path) {
    int number_files = 0;

    DIR *dir = opendir(path);
    while (readdir(dir) != NULL) {
        number_files++;
    }
    closedir(dir);

    return number_files;
}

int main() {

    struct dirent *struct_dirent;
    struct stat struct_stat;
    char file_path[CHAR_BUFFER_SIZE];

    int number_files = get_number_files_in_directory(DIR_PATH);

    // Some kind of HashMap

    // Current index of below arrays
    int counter = 0;
    // Array of different index nodes from files
    int *i_nodes = malloc(number_files * sizeof(int));
    // Array of file names. Each element contains a concatenation of all files which have the same i-node
    char files_names[number_files][CHAR_BUFFER_SIZE];
    // Array of files number. Each element contains the number of files which have the same i-node
    int *count_files = calloc(number_files, sizeof(int));

    DIR *dir = opendir(DIR_PATH);
    while ((struct_dirent = readdir(dir)) != NULL) {

        // Concatenation of directory path and file name.
        // The result will be stored in 'file_path'
        snprintf(file_path, sizeof(file_path), "%s%s", DIR_PATH, struct_dirent->d_name);

        // Write the file with a hard link count of two or more
        if (stat(file_path, &struct_stat) != -1 && struct_stat.st_nlink >= 2 && struct_dirent->d_name[0] != '.') {

            int isExist = 0;

            // Concatenate the file name its i-node is already stored
            for (int i = 0; i < counter; i++) {
                if (i_nodes[i] == struct_dirent->d_ino) {
                    strcat(files_names[i], ", ");
                    strcat(files_names[i], struct_dirent->d_name);
                    count_files[i]++;

                    isExist = 1;
                    break;
                }
            }

            // Write the new i-node in case it hasn't been met before
            if (!isExist) {
                i_nodes[counter] = struct_dirent->d_ino;
                strcpy(files_names[counter], struct_dirent->d_name);
                count_files[counter] = 1;
                counter++;
            }
        }
    }
    closedir(dir);

    // Output the result in ex4.txt file
    // For each such file it should display together all file names that point to the file
    FILE *file = fopen(OUTPUT, "w");
    for (int i = 0; i < counter; i++) {
        fprintf(file, "Index node = %d; Number of files = %d; Files: %s\n", i_nodes[i], count_files[i], files_names[i]);
    }
    fclose(file);

    return 0;
}
