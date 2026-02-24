#include "s21_decimal_extended.h"

#include <stdio.h>

#define S21_MAX_WORD_BITS 32
#define S21_MAX_WORDS 4

static int s21_get_bit_from_int(int value, s21_size nth) {
  return (int)(((uint32_t)value >> nth) & 1u);
}

static void s21_set_bit_from_int(int* value, s21_size nth) {
  uint32_t tmp = (uint32_t)*value;
  tmp |= (1u << nth);
  *value = (int)tmp;
}

static void s21_unset_bit_from_int(int* value, s21_size nth) {
  uint32_t tmp = (uint32_t)*value;
  tmp &= ~(1u << nth);
  *value = (int)tmp;
}

static s21_size s21_resolve_nth_word(s21_size nth) {
  s21_size ret = 0;
  while (nth > S21_MAX_WORD_BITS - 1 && ret < S21_MAX_WORDS) {
    nth -= S21_MAX_WORD_BITS;
    ++ret;
  }

  return (ret < S21_MAX_WORDS) ? ret : (s21_size)-1;
}

bool s21_test_bit(const s21_decimal* value, s21_size nth) {
  const s21_size nth_word = s21_resolve_nth_word(nth);

  bool ret = false;
  if (nth_word != (s21_size)-1) {
    ret = s21_get_bit_from_int(value->bits[nth_word], nth);
  }
  return ret;
}

void s21_set_bit(s21_decimal* value, s21_size nth) {
  const s21_size nth_word = s21_resolve_nth_word(nth);

  if (nth_word != (s21_size)-1) {
    s21_set_bit_from_int(&value->bits[nth_word], nth);
  }
}

void s21_unset_bit(s21_decimal* value, s21_size nth) {
  const s21_size nth_word = s21_resolve_nth_word(nth);

  if (nth_word != (s21_size)-1) {
    s21_unset_bit_from_int(&value->bits[nth_word], nth);
  }
}

s21_sign s21_get_sign(const s21_decimal* value) {
  return (s21_get_bit_from_int(value->bits[3u], 31u) == 0) ? S21_POS_SIGN
                                                           : S21_NEG_SIGN;
}

void s21_set_sign(s21_decimal* value, s21_sign sign) {
  if (sign == S21_POS_SIGN) {
    s21_unset_bit_from_int(&value->bits[3u], 31u);
  } else {
    s21_set_bit_from_int(&value->bits[3u], 31u);
  }
}

s21_size s21_get_scale(const s21_decimal* value) {
  return (s21_size)(((uint32_t)value->bits[3u] >> 16u) & 0xFFu);
}

void s21_set_scale(s21_decimal* value, s21_size scale) {
  const int sign = value->bits[3u] & (int)(1u << 31u);
  value->bits[3u] = sign | ((int)scale << 16u);
}

bool s21_is_zero(const s21_decimal* value) {
  return (value->bits[0u] == 0 && value->bits[1u] == 0 && value->bits[2u] == 0);
}

uint32_t s21_divide_by_10(s21_decimal* value) {
  uint64_t remainder = 0;
  for (int i = 2; i >= 0; --i) {
    const uint64_t acc = (remainder << 32u) | (uint32_t)value->bits[i];
    value->bits[i] = (int)(acc / 10u);
    remainder = acc % 10u;
  }
  return (uint32_t)remainder;
}

void s21_reduce_scale(s21_decimal* value, s21_size scale, bool* has_fraction,
                      uint32_t* last_digit) {
  bool fraction = false;
  uint32_t digit = 0;
  for (s21_size i = 0; i < scale; ++i) {
    digit = s21_divide_by_10(value);
    if (digit != 0) {
      fraction = true;
    }
  }
  if (has_fraction != NULL) {
    *has_fraction = fraction;
  }
  if (last_digit != NULL) {
    *last_digit = digit;
  }
}

void s21_add_one_to_mantissa(s21_decimal* value) {
  uint64_t sum = (uint64_t)(uint32_t)value->bits[0u] + 1u;
  value->bits[0u] = (int)(uint32_t)sum;

  sum = (uint64_t)(uint32_t)value->bits[1u] + (sum >> 32u);
  value->bits[1u] = (int)(uint32_t)sum;

  sum = (uint64_t)(uint32_t)value->bits[2u] + (sum >> 32u);
  value->bits[2u] = (int)(uint32_t)sum;
}
