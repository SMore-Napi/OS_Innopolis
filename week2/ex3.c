#include <stdio.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 3
 */
int main(int args, char *argv[]) {
    int height;
    // In case sscanf has not successfully read
    if (sscanf(argv[1], "%d", &height) != 1) {
        printf("Error argument!");
        return 1;
    }

    int width = 2 * height - 1;

    int star_number = 1;
    for (int i = 0; i < height; i++) {
        int spaces = (width - star_number) / 2;
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }
        for (int j = 0; j < star_number; j++) {
            printf("*");
        }
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }
        printf("\n");

        star_number += 2;
    }

    return 0;
}
