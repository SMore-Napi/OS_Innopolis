#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <stdio.h>

#define    MEM_SIZE 10*1024*1024    // 10MB

/**
 * Roman Soldatov BS19-02
 * Exercise 4
 */
int main() {
    struct rusage r_usage;

    for (int i = 0; i < 10; i++) {
        int *p = (int *) malloc(MEM_SIZE);
        memset(p, 0, MEM_SIZE);
        getrusage(RUSAGE_SELF, &r_usage);
        printf("Memory usage (ru_maxrss): %ld\n", r_usage.ru_maxrss);
        sleep(1);
    }

    return 0;
}

