#ifndef THIRD_METHODS_H
#define THIRD_METHODS_H


typedef double (*Function)(double);
double binary_search(Function, double start, double end,
                     double e, unsigned int *count, double *error);

double iteration(Function, Function,
                 double start, double end, double e,
                 unsigned int *count, double *error);

double newton(Function, double start, double end, double e,
              unsigned int *count, double *error);
#endif
