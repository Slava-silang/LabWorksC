//
// Created by slava on 27.10.2026.
//

#ifndef THIRD_FUNCTIONS_H
#define THIRD_FUNCTIONS_H
enum BATHIS {
    ITERATION,
    NEWTON
};
static int check_line_segment(double(* function)(double) ,double *start, double *end);
static double derivative(double(* function)(double), double x);
static double second_derivative(double(* function)(double), double x);
double binary_search(double(* function)(double), double start, double end, double e, unsigned int *count);
double iteration(double(* function)(double), double start, double end, double e, unsigned int *count);
int make_iteration(double(* function)(double), double *x, double *x_1, enum BATHIS);
#endif //THIRD_FUNCTIONS_H
