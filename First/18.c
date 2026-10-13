#include <stdio.h>
#include <stdint.h>
#define int int32_t
#define uint uint32_t

union translator {
    float first;
    int second;
};

uint add_bits(uint first, uint second) {
    while (second != 0) {
        uint carry = (first & second) << 1;
        first = first ^ second;
        second = carry;
    }
    return first;
}

int main() {
    printf("\nThis program summarizes two float numbres\n");

    float first_number, second_number;

    printf("Write first number: ");
    scanf("%f", &first_number);
    printf("\nWrite second number: ");
    scanf("%f", &second_number);

    union translator first_trans;
    union translator second_trans;

    first_trans.first = first_number;
    second_trans.first = second_number;

    uint remake_first = first_trans.second;
    uint remake_second = second_trans.second;

    int first_sign = (remake_first >> 31) & 1;
    int second_sign = (remake_second >> 31) & 1;

    int first_exp = -127; 
    int second_exp = -127;

    first_exp += (remake_first >> 23) & (1UL << 8) - 1;
    second_exp += (remake_second >> 23) & (1UL << 8) - 1;

    uint first_mantissa = remake_first & (1UL << 23) - 1 | 1UL << 23;
    uint second_mantissa = remake_second & (1UL << 23) - 1 | 1UL << 23;

    while (first_exp < second_exp) {
        first_mantissa >>= 1;
        first_exp++;
    }

    while (second_exp < first_exp) {
        second_mantissa >>= 1;
        second_exp++;
    }

    int result_exp = first_exp;
    int result_sign;

    uint result_mantissa;

    if (first_sign == second_sign) {
        result_mantissa = add_bits(first_mantissa, second_mantissa);
        result_sign = first_sign;

        if (result_mantissa & 1UL << 24) {
            result_mantissa >>= 1;
            result_exp++;
        }
    } else {
        if (first_sign) {
            first_mantissa = add_bits(~first_mantissa, 1);
        } else {
            second_mantissa = add_bits(~second_mantissa, 1);
        }

        result_mantissa = add_bits(first_mantissa, second_mantissa);

        result_sign = result_mantissa >> 31 & 1;

        if (result_sign) {
            result_mantissa = add_bits(~result_mantissa, 1);
        }

        while ((result_mantissa & 1UL << 23) == 0) {
            result_mantissa <<= 1;
            result_exp--;
        }
    }

    if (result_exp > 127) {
        fprintf(stderr, "\nOverflow occurred\n");
        return 2;
    }

    if (result_exp < -126) {
        fprintf(stderr, "\nUnderflow occurred\n");
        return 2;
    }

    union translator result_trans;
    result_trans.second = (result_sign << 31) | ((result_exp + 127) << 23) | (result_mantissa & (1UL << 23) - 1);
    printf("\nResult: %.5f\n", result_trans.first);
    return 0;
}