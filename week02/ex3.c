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
    int stars_count = 1;

    // Print triangle
    for (int i = 0; i < height; i++) {
        int spaces = (width - stars_count) / 2;

        // Print spaces before stars
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }

        // Print stars
        for (int j = 0; j < stars_count; j++) {
            printf("*");
        }

        // Print spaces after stars
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }
        printf("\n");

        stars_count += 2;
    }

    return 0;
}
