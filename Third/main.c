#include <math.h>
#include <stdio.h>
#include "methods.h"

static double h = 0x1p-20;

int main() {
    return 0;
}
static int check_line_segment(double(* function)(double) ,double *start, double *end) {
    if (function(*end) * function(*start) > 0) {
        fprintf(stderr, "This line segment does not have a root.");
        return 1;
    }
    if (*start > *end) {
        *start = *start + *end;
        *end = *start - *end;
        *start = *start - *end;
    }
    return 0;
}
static double derivative(double(* function)(double), const double x) {
    return (function(x + h) - function(x - h)) / (2 * h);
}

static double second_derivative(double(* function)(double), const double x) {
    return (function(x + h) - 2*function(x) + function(x - h)) / (h * h);
}

double binary_search(
    double(* function)(double),
    double start,
    double end,
    const double e,
    unsigned int *count)
{
    if (check_line_segment(function, &start, &end)) {
        return 1;
    }

    if (function(start) == 0) {
        return start;
    }
    if (function(end) == 0) {
        return end;
    }

    double result = 0;

    while (end - start > 2 * e) {
        result = (end + start) / 2;

        if (function(result) == 0)
            return result;

        if (function(result)*function(start) > 0)
            start = result;
        else
            end = result;

        *count = *count + 1;
    }
    return (start + end) / 2;
}

double iteration(
    double(* function)(double),
    double start,
    double end,
    const double e,
    unsigned int *count) {

    if (check_line_segment(function, &start, &end)) {
        return 1;
    }

    if (function(start) == 0) {
        return start;
    }
    if (function(end) == 0) {
        return end;
    }

    double x = (start + end) / 2;

    if (function(x) == 0) {
        return x;
    }

    if (derivative(function, x) >= 1) {
        fprintf(stderr, "Convergence conditions are not met.");
        return 1;
    }

    double x_1 = function(x) + x;
    *count = 1;

    if (function(x_1) == 0) {
        return x_1;
    }

    while (fabs(x - x_1) > e) {
        if (make_iteration(function, &x, &x_1, ITERATION)) {
            return 1;
        }
        *count = *count + 1;

        if (function(x) == 0) {
            return x;
        }
    }
    return x_1;
}

double newton(
    double(* function)(double),
    double start,
    double end,
    const double e,
    unsigned int *count) {

    if (check_line_segment(function, &start, &end)) {
        return 1;
    }

    if (function(start) == 0) {
        return start;
    }
    if (function(end) == 0) {
        return end;
    }

    double x = (start + end) / 2;
    if (function(x) == 0) {
        return x;
    }
    if (fabs(function(x) * second_derivative(function, x)) >= pow(derivative(function, x), 2)) {
        fprintf(stderr, "Convergence conditions are not met.");
        return 1;
    }

    double x_1 = x - (function(x) / derivative(function, x));
    *count = *count + 1;
    if (function(x_1) == 0) {
        return x_1;
    }

    while (fabs(x - x_1) > e) {
        if (make_iteration(function, &x, &x_1, NEWTON)) {
            return 1;
        }
        *count = *count + 1;
        if (function(x) == 0) {
            return x;
        }
    }
    return x_1;
}

int make_iteration(double(* function)(double), double *x, double *x_1, const enum BATHIS b) {
    if (b == ITERATION) {
        if (fabs(derivative(function, *x_1)) >= 1) {
            fprintf(stderr, "Convergence conditions are not met.");
            return 1;
        }

        *x = *x_1;
        *x_1 = function(*x) + *x;
        return 0;
    }

    if (fabs(function(*x_1) * second_derivative(function, *x_1)) >= pow(derivative(function, *x_1), 2)) {
        fprintf(stderr, "Convergence conditions are not met.");
        return 1;
    }

    *x = *x_1;
    *x_1 = *x - (function(*x) / derivative(function, *x));
    return 0;
}

