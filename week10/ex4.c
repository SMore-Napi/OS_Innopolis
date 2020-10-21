#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define DIR_PATH "./tmp/"
#define OUTPUT_PATH "ex4.txt"
#define CHAR_BUFFER_SIZE 255 // The string size

/**
 * Roman Soldatov BS19-02
 * Exercise 4
 */

/**
 * The program output:
 * For index node = 15194123 there are 2 files: link1, file1
 *
 * Also, it is duplicated in ex4.txt file
 */

/**
 * Structure for storing a different kind of information about files
 */
struct dir_information {
    // Current index of below arrays
    int counter;
    // Array of different index nodes from files
    int *i_nodes;
    // Array of file names. Each element contains a concatenation of all files which have the same i-node
    char **files_names;
    // Array of files number. Each element contains the number of files which have the same i-node
    int *count_files;
};

/**
 * Function declarations
 */

/**
 * Return the number of files in the given directory
 */
int get_number_files_in_directory(char *path);

void initialize_dir_information(int number_files, struct dir_information *info);

void insert_file_information(struct dir_information *info, struct dirent *struct_dirent);

/**
 * Scan given directory and locates all i-nodes with a hard link count of two or more
 */
void find_all_files_in_directory(char *path, struct dir_information *info);

/**
 * For each such file it should display together all file names that point to the file
 */
void print_result(char *path, struct dir_information *info);

void free_dir_information(struct dir_information *info, int number_files);

int main() {

    int number_files = get_number_files_in_directory(DIR_PATH);

    struct dir_information info;
    initialize_dir_information(number_files, &info);

    // Find all files in tmp directory and fill i-node information about them in 'info'.
    find_all_files_in_directory(DIR_PATH, &info);

    // Output the obtained result from 'info' in ex4.txt file
    print_result(OUTPUT_PATH, &info);

    // Free memory allocation of 'info'
    free_dir_information(&info, number_files);

    return 0;
}

/**
 * Function implementations
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

void initialize_dir_information(int number_files, struct dir_information *info) {
    info->counter = 0;

    info->i_nodes = malloc(number_files * sizeof(int));

    info->files_names = malloc(number_files * sizeof(char *));
    for (int i = 0; i < number_files; i++) {
        info->files_names[i] = malloc(CHAR_BUFFER_SIZE * sizeof(char));
    }

    info->count_files = calloc(number_files, sizeof(int));
}

void insert_file_information(struct dir_information *info, struct dirent *struct_dirent) {

    // Look for existing i-nodes
    for (int i = 0; i < info->counter; i++) {
        // Concatenate the file name if its i-node is already stored
        if (info->i_nodes[i] == struct_dirent->d_ino) {
            strcat(info->files_names[i], ", ");
            strcat(info->files_names[i], struct_dirent->d_name);
            info->count_files[i]++;
            return;
        }
    }

    // Write the new i-node in case it hasn't been met before
    info->i_nodes[info->counter] = struct_dirent->d_ino;
    strcpy(info->files_names[info->counter], struct_dirent->d_name);
    info->count_files[info->counter] = 1;
    info->counter++;
}

void find_all_files_in_directory(char *path, struct dir_information *info) {

    struct dirent *struct_dirent;
    struct stat struct_stat;
    char file_path[CHAR_BUFFER_SIZE];
    char new_recursive_path[CHAR_BUFFER_SIZE];

    DIR *dir = opendir(path);
    while ((struct_dirent = readdir(dir)) != NULL) {

        // In case it is a folder
        if (struct_dirent->d_type == DT_DIR) {
            // Ignore '.' and '..' folders
            if (strcmp(struct_dirent->d_name, ".") != 0 && strcmp(struct_dirent->d_name, "..") != 0) {
                // Create the path for the sub folder
                strcpy(new_recursive_path, path);
                strcat(new_recursive_path, struct_dirent->d_name);
                strcat(new_recursive_path, "/");

                // Go to the folder recursively
                find_all_files_in_directory(new_recursive_path, info);
            }
        } else {
            // Concatenation of directory path and file name.
            // The result will be stored in 'file_path'
            snprintf(file_path, sizeof(file_path), "%s%s", path, struct_dirent->d_name);

            // Write the file with a hard link count of two or more
            if (stat(file_path, &struct_stat) != -1 && struct_stat.st_nlink >= 2) {
                insert_file_information(info, struct_dirent);
            }
        }
    }

    closedir(dir);
}

void print_result(char *path, struct dir_information *info) {
    FILE *file = fopen(path, "w");
    for (int i = 0; i < info->counter; i++) {
        fprintf(file, "For index node = %d there are %d files: %s\n", info->i_nodes[i], info->count_files[i],
                info->files_names[i]);
    }
    fclose(file);
}

void free_dir_information(struct dir_information *info, int number_files) {
    free(info->i_nodes);
    for (int i = 0; i < number_files; i++) {
        free(info->files_names[i]);
    }
    free(info->files_names);
    free(info->count_files);
}
