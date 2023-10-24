#include "auxiliary_functions.h"

int is_digit(int symb) {
  int res = 0;
  if (symb >= '0' && symb <= '9') res = 1;
  return res;
}

int is_space(int symb) {
  int res = 0;
  if (symb == ' ' || symb == '\t' || symb == '\n' || symb == '\r' ||
      symb == '\f' || symb == '\v')
    res = 1;
  return res;
}

int parse_prenumber(realized_size_t *count, int *sign, realized_size_t width, int *base,
                    const char **str) {
  int result = 0;
  while (is_space(**str)) {
    (*str)++;
  }
  if (**str == '-') {
    *sign = -1;
    (*str)++;
    (*count)++;
  } else if (**str == '+') {
    (*str)++;
    (*count)++;
  }

  if (*base == 0 || *base == 16) {
    int new_base = 10;
    if (**str == '0' && ((*count)++ < width || width == 0)) {
      result = 1;
      new_base = 8;
      (*str)++;
      if ((**str == 'x' || **str == 'X') &&
          ((*count)++ < width || width == 0)) {
        new_base = 16;
        (*str)++;
      }
    }
    if (*base == 0) *base = new_base;
  }
  return result;
}

int char_to_digit(char c, int base) {
  int digit = -1;
  if (is_digit(c)) {
    digit = c - '0';
  } else if (base == 16) {
    if (c >= 'a' && c <= 'f') {
      digit = c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
      digit = c - 'A' + 10;
    }
  }
  return digit;
}

int str_to_int(const char **str, long long *value, realized_size_t width, int base) {
  int sign = 1;
  long long result = 0;
  int overflow = 0;
  realized_size_t count = 0;

  int res = parse_prenumber(&count, &sign, width, &base, str);
  while (count++ < width || width == 0) {
    int digit = char_to_digit(**str, base);
    if (digit >= 0 && digit < base) {
      res = 1;
      if (overflow == 0) {
        if (result > (LONG_MAX - digit) / base) {
          overflow = 1;
          result = (sign == 1) ? LONG_MAX : LONG_MIN;
          sign = 1;
        } else {
          result = result * base + digit;
        }
      }
      (*str)++;
    } else {
      break;
    }
  }
  *value = sign * result;

  return res;
}

int str_to_uint(const char **str, unsigned long long *value, realized_size_t width,
                int base) {
  int sign = 1;
  unsigned long long result = 0;
  int overflow = 0;
  realized_size_t count = 0;

  int res = parse_prenumber(&count, &sign, width, &base, str);

  while (count++ < width || width == 0) {
    int digit = char_to_digit(**str, base);

    if (digit >= 0 && digit < base) {
      res = 1;
      if (!overflow) {
        if (result > (ULONG_MAX - digit) / base) {
          overflow = 1;
          result = ULONG_MAX;
          sign = 1;
        } else {
          result = result * base + digit;
        }
      }
      (*str)++;
    } else {
      break;
    }
  }
  *value = sign * result;

  return res;
}

int str_to_float_overflow(const char **str, long double *value,
                          realized_size_t width, realized_size_t *count, int *sign,
                          int base) {
  int res = 0;
  int overflow = 0;
  while (*count < width || width == 0) {
    int digit = char_to_digit(**str, base);

    if (digit >= 0 && digit < base) {
      res = 1;
      (*count)++;
      if (!overflow) {
        if (*value > (LDBL_MAX - digit) / base) {
          overflow = 1;
          *value = (*sign == 1) ? LDBL_MAX : LDBL_MIN;
          *sign = 1;
        } else {
          *value = *value * base + digit;
        }
      }
      (*str)++;
    } else {
      break;
    }
  }
  return res;
}

int str_to_float(const char **str, long double *value, realized_size_t width) {
  int sign = 1;
  int base = 10;
  realized_size_t count = 0;
  realized_size_t decimal_places = 0;
  long double integer_part = 0;
  long double decimal_part = 0;
  long long exponent = 0;

  int res = parse_prenumber(&count, &sign, width, &base, str);
  if (**str == 'n' || **str == 'N' || **str == 'i' || **str == 'I') {
    return edge_values(str, width, count, sign, value);
  }
  res = str_to_float_overflow(str, &integer_part, width, &count, &sign, base) ||
        res;
  if (**str == '.' && (count < width || width == 0)) {
    (*str)++;
    count++;
    decimal_places = count;
    res =
        str_to_float_overflow(str, &decimal_part, width, &count, &sign, base) ||
        res;
    decimal_places = count - decimal_places;
  }
  if ((**str == 'e' || **str == 'E') && (count++ < width || width == 0)) {
    (*str)++;
    str_to_int(str, &exponent, width - count, 10);
  }
  *value = sign * ((integer_part + decimal_part / pow(10, decimal_places)) *
                   pow(10, exponent));

  return res;
}

int edge_values(const char **str, realized_size_t width, realized_size_t count, int sign,
                long double *value) {
  int res = 0;
  char temp[9] = {'\0'};
  char *temp_lower = realized_to_lower(realized_strncpy(temp, *str, 8));
  if ((count + 8 <= width || width == 0) &&
      realized_strncmp(temp_lower, "infinity", 8) == 0) {
    (*str) += 8;
    *value = sign * INFINITY;
    res = 1;
  } else if (count + 3 <= width || width == 0) {
    if (realized_strncmp(temp_lower, "inf", 3) == 0) {
      (*str) += 3;
      *value = sign * INFINITY;
      res = 1;
    } else if (realized_strncmp(temp_lower, "nan", 3) == 0) {
      (*str) += 3;
      *value = sign * NAN;
      res = 1;
    }
  }
  free(temp_lower);
  return res;
}