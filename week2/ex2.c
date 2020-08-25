#include <stdio.h>
#include <string.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 2
 */
int main() {

    // Prompt the user for a string
    printf("Enter a string:\n");

    // Input string
    char *string;
    scanf("%[^\n]", string);

    // Get the length of a string
    int length = strlen(string);

    // Print string reverse
    for (int i = length - 1; i >= 0; i--) {
        printf("%c", string[i]);
    }

    return 0;
}
