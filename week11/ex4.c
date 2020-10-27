#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define SOURCE_FILE_PATH "ex1.txt"
#define DESTINATION_FILE_PATH "ex1.memcpy.txt"

/**
 * Roman Soldatov BS19-02
 * Exercise 1
 */

void copy_content(const char *source_file_path, const char *destination_file_path) {
    // Open files
    int src_file = open(source_file_path, O_RDONLY);
    int dest_file = open(destination_file_path, O_CREAT | O_RDWR, 0777);

    // Get the source file size
    struct stat struct_stat;
    fstat(src_file, &struct_stat);

    char *src = mmap(NULL, struct_stat.st_size, PROT_READ, MAP_SHARED, src_file, 0);

    // Change the destination file size
    ftruncate(dest_file, struct_stat.st_size);
    char *dest = mmap(NULL, struct_stat.st_size, PROT_WRITE, MAP_SHARED, dest_file, 0);

    // Copy bytes from source file to destination file
    memcpy(dest, src, struct_stat.st_size);

    munmap(src, struct_stat.st_size);
    munmap(dest, struct_stat.st_size);
    close(src_file);
    close(dest_file);
}

int main() {
    copy_content(SOURCE_FILE_PATH, DESTINATION_FILE_PATH);
    return 0;
}
