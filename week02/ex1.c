#include <stdio.h>
#include <limits.h>
#include <float.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 1
 */
int main() {

    // Declare integer, float and double variables
    int int_variable;
    float float_variable;
    double double_variable;

    // Assign maximum values for each variable
    int_variable = INT_MAX;
    float_variable = FLT_MAX;
    double_variable = DBL_MAX;

    // Print sizes and values of each variable
    printf("Integer: size = %lu, max value = %d \n", sizeof(int_variable), int_variable);
    printf("Float: size = %lu, max value = %f \n", sizeof(float_variable), float_variable);
    printf("Double: size = %lu, max value = %f \n", sizeof(double_variable), double_variable);

    return 0;
}
