#include <math.h>
#include <stdio.h>

int main(void) {
    double x;

    if (scanf("%lf", &x) != 1) {
        return 1;
    }

    printf("%f\n", sqrt(x));
    return 0;
}