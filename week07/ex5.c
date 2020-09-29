#include <stdio.h>
#include <stdlib.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 5
 */
int main() {
    char **s;
    char foo[] = "Hello World";

    //1st change: Add new line
    s = malloc(sizeof(char *));

    *s = foo;

    // 2nd change: correct this line
    printf("s is %s\n", *s);
    // Another possible solution, if you want print an address
    // printf("s is %p\n", s);

    s[0] = foo;
    printf("s[0] is %s\n", s[0]);
    return (0);
}