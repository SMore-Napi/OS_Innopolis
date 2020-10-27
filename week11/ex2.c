#include <stdio.h>
#include <unistd.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 2
 */

void print_word(const char *string) {
    setvbuf(stdout, 0, _IOLBF, 6);

    for (int i = 0; i < 6; i++) {
        printf("%c", string[i]);
        sleep(1);
    }
}

int main() {
    print_word("Hello");
    return 0;
}
