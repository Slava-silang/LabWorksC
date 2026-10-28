#include <math.h>
#include <stdio.h>
#include "methods.h"
#include "functions.h"
#define EPSILON 1e-5
#define FIRST_ROOT 2.0692
#define SECOND_ROOT 0.5768
#define THIRD_ROOT 0.9892

int main(void) {
    unsigned int count = 0;
    double error = 0;
    double start = 1, end = 3;
    double root = 0;
    printf("First function is 3x - 14 + e^x - e^(-x)\n");
    printf("Tabular value of a root in [%.1lf;%.1lf] is %f\n",start, end, FIRST_ROOT);
    printf("Found value\n");
    root = binary_search(first_function, start, end, EPSILON, &count, &error);
    if (isnan(root)) {
        return 1;
    }
    printf("    By binary search is %lf with %.15lf error in %u steps\n", root, error, count);
    root = iteration(first_function, first_function_phi, start, end, EPSILON, &count, &error);
    if (isnan(root)) {
        return 1;
    }
    printf("    By iteration is %lf with %.15lf error in %u steps\n", root, error, count);
    root = newton(first_function, start, end, EPSILON, &count, &error);
    if (isnan(root)) {
        return 1;
    }
    printf("    By newton is %lf with %.15lf error in %u steps\n", root, error, count);
    printf("\n");
    start = 0;
    end = 1;
    printf("Second function is square root of (1 - x) - tg(x)\n");
    printf("Tabular value of a root in [%.1lf;%.1lf] is %f\n", start, end, SECOND_ROOT);
    printf("Found value\n");
    root = binary_search(second_function, start, end, EPSILON, &count, &error);
    if (isnan(root)) {
        return 1;
    }
    printf("    By binary search is %lf with %.15lf error in %u steps\n", root, error, count);
    root = iteration(second_function, second_function_phi, start, end, EPSILON, &count, &error);
    if (isnan(root)) {
        return 1;
    }
    printf("    By iteration is %lf with %.15lf error in %u steps\n", root, error, count);
    root = newton(second_function, start, end, EPSILON, &count, &error);
    if (isnan(root)) {
        return 1;
    }
    printf("    By newton is %lf with %.15lf error in %u steps\n", root, error, count);
    printf("\n");
    start = 0.5;
    end = 1.5;
    printf("Third function is x + cos(x^0,52 + 2)\n");
    printf("Tabular value of a root in [%.1lf;%.1lf] is %f\n", start, end, THIRD_ROOT);
    printf("Found value\n");
    root = binary_search(third_function, start, end, EPSILON, &count, &error);
    if (isnan(root)) {
        return 1;
    }
    printf("    By binary search is %lf with %.15lf error in %u steps\n", root, error, count);
    root = iteration(third_function, third_function_phi, start, end, EPSILON, &count, &error);
    if (isnan(root)) {
        return 1;
    }
    printf("    By iteration is %lf with %.15lf error in %u steps\n", root, error, count);
    root = newton(third_function, start, end, EPSILON, &count, &error);
    if (isnan(root)) {
        return 1;
    }
    printf("    By newton is %lf with %.15lf error in %u steps\n", root, error, count);
    return 0;
}
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/