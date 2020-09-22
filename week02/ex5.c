#include <stdio.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 5
 */

/**
     *
    ***
   *****
  *******
 *********
***********
 */
void print_figure1(int height) {
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
}

/**
*
**
***
****
*****
******
*******
 */
void print_figure2(int height) {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

/**
*
**
***
****
***
**
*
 */
void print_figure3(int height) {
    // Calculate the width
    int width = height / 2;
    if (height % 2 != 0) {
        width++;
    }

    // Print the upper side of a triangle
    for (int i = 1; i <= width; i++) {
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    // In case of even height double the line with stars count = width
    if (height % 2 == 0) {
        for (int j = 1; j <= width; j++) {
            printf("*");
        }
        printf("\n");
    }

    // Print the lower side of a triangle
    for (int i = width - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

/**
*******
*******
*******
*******
*******
*******
*******
 */
void print_figure4(int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; j++) {
            printf("*");
        }
        printf("\n");
    }
}

int main(int args, char *argv[]) {
    int n;
    int figure_type;

    // In case sscanf has not successfully read
    if (sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &figure_type) != 1) {
        printf("Error argument!");
        return 1;
    }

    switch (figure_type) {
        case 1:
            print_figure1(n);
            break;
        case 2:
            print_figure2(n);
            break;
        case 3:
            print_figure3(n);
            break;
        case 4:
            print_figure4(n);
            break;
        default:
            printf("Wrong figure type!");
    }

    return 0;
}
