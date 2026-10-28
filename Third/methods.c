//
// Created by slava on 29.10.2026.
//
#include <math.h>
#include <stdio.h>
#include "methods.h"
#ifndef MAX_COUNT
#define MAX_COUNT 1000
#endif

static int check_line_segment(
    double (*function)(double),
    double *start,
    double *end,
    double e)
{
    if (!isfinite(*start) || !isfinite(*end) || !isfinite(e) || e <= 0) {
        fprintf(stderr, "Incorrect interval or accuracy.\n");
        return 1;
    }
    if (*start > *end) {
        double temp = *start;
        *start = *end;
        *end = temp;
    }
    double left = function(*start);
    double right = function(*end);
    if (!isfinite(left) || !isfinite(right)) {
        fprintf(stderr, "Incorrect function value.\n");
        return 1;
    }
    if ((left > 0 && right > 0) || (left < 0 && right < 0)) {
        fprintf(stderr, "No sign change on the interval.\n");
        return 1;
    }
    return 0;
}

static double derivative(double (*function)(double), double x) {
    double h = 1e-5 * fmax(1, fabs(x));
    double left = x - h;
    double right = x + h;
    if (left == right)
        return NAN;
    return (function(right) - function(left)) / (right - left);
}

static double second_derivative(double (*function)(double), double x) {
    double h = 1e-5 * fmax(1, fabs(x));
    return (function(x + h) - 2 * function(x) + function(x - h))
       / (h * h);
}

double binary_search(Function function,
                     double start,
                     double end,
                     double e,
                     unsigned int *count,
                     double *error)
{
    *count = 0;
    *error = INFINITY;
    if (check_line_segment(function, &start, &end, e))
        return NAN;

    if (function(start) == 0) {
        *error = 0;
        return start;
    }
    if (function(end) == 0) {
        *error = 0;
        return end;
    }

    double x = start / 2 + end / 2;
    *error = fmax(x - start, end - x);
    while (*error >= e) {
        double value = function(x);
        if (!isfinite(value)) {
            fprintf(stderr, "Incorrect function value.\n");
            return NAN;
        }
        if (value == 0) {
            *error = 0;
            return x;
        }
        if (*count >= MAX_COUNT || x == start || x == end) {
            fprintf(stderr, "Required accuracy was not reached.\n");
            return NAN;
        }
        if ((value > 0 && function(start) > 0) ||
            (value < 0 && function(start) < 0))
            start = x;
        else
            end = x;

        *count = *count + 1;
        x = start / 2 + end / 2;
        *error = fmax(x - start, end - x);
    }
    return x;
}

double iteration(Function function,
                 Function phi,
                 double start,
                 double end,
                 double e,
                 unsigned int *count,
                 double *error)
{
    *count = 0;
    *error = INFINITY;
    if (check_line_segment(function, &start, &end, e))
        return NAN;
    if (function(start) == 0) {
        *error = 0;
        return start;
    }
    if (function(end) == 0) {
        *error = 0;
        return end;
    }

    double x = start / 2 + end / 2;

    while (1) {
        double value = function(x);
        if (!isfinite(value)) {
            fprintf(stderr, "Incorrect function value.\n");
            return NAN;
        }
        if (value == 0) {
            *error = 0;
            return x;
        }
        if (*error < e)
            return x;

        double df = derivative(phi, x);

        if (fabs(df) >= 1 || !isfinite(df)) {
            fprintf(stderr, "Convergence conditions are not met.");
            return NAN;
        }

        if (*count >= MAX_COUNT) {
            fprintf(stderr, "Iteration limit reached.\n");
            return NAN;
        }

        double x_1 = phi(x);

        if (!isfinite(x_1)) {
            fprintf(stderr, "Iteration cannot continue.\n");
            return NAN;
        }
        if (x_1 < start || x_1 > end) {
            fprintf(stderr, "x is out of line segment.\n");
        }

        *error = fabs(x_1 - x);
        x = x_1;
        *count = *count + 1;
    }
}

double newton(Function function,
              double start,
              double end,
              double e,
              unsigned int *count,
              double *error)
{
    *count = 0;
    *error = INFINITY;
    if (check_line_segment(function, &start, &end, e))
        return NAN;
    if (function(start) == 0) {
        *error = 0;
        return start;
    }
    if (function(end) == 0) {
        *error = 0;
        return end;
    }

    double x = start / 2 + end / 2;

    while (1) {
        double value = function(x);

        if (!isfinite(value)) {
            fprintf(stderr, "Incorrect function value.\n");
            return NAN;
        }

        if (value == 0) {
            *error = 0;
            return x;
        }

        if (*error < e)
            return x;

        double df = derivative(function, x);
        double df2 = second_derivative(function, x);

        if (!isfinite(df2) || !isfinite(df) || fabs(value * df2) >= df * df) {
            fprintf(stderr, "Convergence conditions are not met.");
            return NAN;
        }

        if (*count >= MAX_COUNT) {
            fprintf(stderr, "Iteration limit reached.\n");
            return NAN;
        }

        double x_1 = x - value / df;
        *error = fabs(x_1 - x);

        if (!isfinite(x_1)) {
            fprintf(stderr, "Newton method cannot continue.\n");
            return NAN;
        }
        if (x_1 < start || x_1 > end) {
            fprintf(stderr, "x is out of line segment.\n");
            return NAN;
        }
        x = x_1;
        *count = *count + 1;
    }
}