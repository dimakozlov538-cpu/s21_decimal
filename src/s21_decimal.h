#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

// Sign Values (bits[3])
#define S21_SIGN_POSITIVE 0
#define S21_SIGN_NEGATIVE (1 << 31)

// Conversion Status Codes
#define S21_CONVERSION_OK 0
#define S21_CONVERSION_ERROR 1

// Limits
#define S21_MAX_FLOAT 7.9228162514264337593543950335e28

// Data Structure
typedef struct {
    int bits[4];
} s21_decimal;

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);  // Addition
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);  // Subtraction
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);  // Multiplication
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);  // Division

// Comparison Operators
int s21_is_less(s21_decimal, s21_decimal);              // Less than
int s21_is_less_or_equal(s21_decimal, s21_decimal);     // Less than or equal to
int s21_is_greater(s21_decimal, s21_decimal);           // Greater than
int s21_is_greater_or_equal(s21_decimal, s21_decimal);  // Greater than or equal to
int s21_is_equal(s21_decimal, s21_decimal);             // Equal to
int s21_is_not_equal(s21_decimal, s21_decimal);         // Not equal to

// Convertors and Parsers
int s21_from_int_to_decimal(int src, s21_decimal* dst);      // From int
int s21_from_float_to_decimal(float src, s21_decimal* dst);  // From float
int s21_from_decimal_to_int(s21_decimal src, int* dst);      // To int
int s21_from_decimal_to_float(s21_decimal src, float* dst);  // To float

// Other Functions
int s21_floor(s21_decimal value, s21_decimal* result);  // Rounds a specified Decimal number to the closest
                                                        // integer toward negative infinity.
int s21_round(s21_decimal value, s21_decimal* result);  // Rounds a decimal value to the nearest integer.
int s21_truncate(s21_decimal value,
                 s21_decimal* result);  // Returns the integral digits of the specified Decimal; any
                                        // fractional digits are discarded, including trailing zeroes.
int s21_negate(
    s21_decimal value,
    s21_decimal* result);  // Returns the result of multiplying the specified Decimal value by negative one.

#endif  // S21_DECIMAL_H
