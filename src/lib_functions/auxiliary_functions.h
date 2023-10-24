#include "../realized_string.h"

int is_digit(int symb);
int is_space(int symb);
int parse_prenumber(realized_size_t *count, int *sign, realized_size_t width, int *base,
                    const char **str);
int char_to_digit(char c, int base);
int str_to_int(const char **str, long long *value, realized_size_t width, int base);
int str_to_uint(const char **str, unsigned long long *value, realized_size_t width,
                int base);
int str_to_float_overflow(const char **str, long double *value,
                          realized_size_t width, realized_size_t *count, int *sign,
                          int base);
int str_to_float(const char **str, long double *value, realized_size_t width);
int edge_values(const char **str, realized_size_t width, realized_size_t count, int sign,
                long double *value);