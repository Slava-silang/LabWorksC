#include <stdio.h>
#include <stdint.h>
#define int int32_t
#define MIN_START 1
#define MAX_START 31
#define MIN_END 1
#define MAX_END 32

int main() {
    int number;
    printf("This program print binary digits of number type int_32\n");
    printf("Write your number: ");
    scanf("%d", &number);

    int start;
    int end;

    printf("Write first digit: ");
    scanf("%d", &start);

    if(start < MIN_START || start > MAX_START) {
        fprintf(stderr, "Start digit is invalid.\nAllowed: from %d to %d\n", MIN_START, MAX_START);
        return 2;
    }

    printf("Write last digit: ");
    scanf("%d", &end);

    if(end < MIN_END || end > MAX_END) {
        fprintf(stderr, "Last digit is invalid.\nAllowed: from %d to %d\n", MIN_END, MAX_END);
        return 2;
    }

    if(end < start) {
        fprintf(stderr, "Start cannot be greater than end\n");
        return 2;
    }

    printf("\n");

    for(int i = 0; i < end - start + 1; ++i) {
        int c;
        c = (number >> (end - i - 1)) & 1;
        printf("%d", c);

    }
    printf("\n");
    return 0;
}