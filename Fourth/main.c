#include <stdio.h>
#include <math.h>
#define MAX_ITER 100

double machine_epsilon() {
    double eps = 1;
    volatile double probe;

    while (1) {
        probe = 1 + eps / 2.0;

        if (probe == 1)
            return eps;

        eps /= 2.0;
    }
}

int taylor_log(double x, double tolerance,
               double *result, int *count)
{
    double sum = log(2.0);
    double temp = x / 2.0;

    *count = 0;

    while (*count < MAX_ITER) {
        ++(*count);

        sum = (*count % 2 == 1) ? sum + temp : sum - temp;

        temp *= (x / 2.0) * ((double)*count / (*count + 1));

        *result = sum;

        if (fabs(temp) / (1.0 - fabs(x / 2.0)) <= tolerance)
            return 1;
    }

    return 0;
}

int main() {
    double eps = machine_epsilon();
    double k;
    int n;
    printf("Enter n, k: ");
    scanf("%d", &n);
    scanf("%lf", &k);
    double tolerance = eps*k;
    double a = -1.0, b = 1.0;
    printf("%5s | %22s | %22s | %22s | %12s | %5s | %s\n",
               "i", "x", "Taylor", "ln(2+x)", "abs diff",
               "terms", "status");
    for (int i = 0; i <= n; ++i) {
            double x;

            x = a + (b - a) * ((double)i / n);

            double approx;
            int count;

            int status = taylor_log(
                x, tolerance, &approx, &count
            );

            double reference = log(2.0 + x);
            double difference = fabs(approx - reference);

            printf("%5d | %22.16f | %22.16f | %22.16f | "
                   "%12.4e | %5d | %s\n",
                   i, x, approx, reference, difference,
                   count, status ? "OK" : "LIMIT");
        }
    return 0;
}
