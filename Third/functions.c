//
// Created by slava on 29.10.2026.
//
#include <math.h>
#include "functions.h"

double first_function(double x) {
    return 3 * x - 14 + exp(x) - exp(-x);
}

double first_function_phi(double x) {
    return log(14 + exp(-x) - 3 * x);
}

double second_function(double x) {
    return sqrt(1 - x) - tan(x);
}

double second_function_phi(double x) {
    return atan(sqrt(1-x));
}

double third_function(double x) {
    return x + cos(pow(x, 0.52) + 2);
}

double third_function_phi(double x) {
    return -cos(pow(x, 0.52) + 2);
}