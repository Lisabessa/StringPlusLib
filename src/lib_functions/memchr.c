#include "../realized_string.h"

void *realized_memchr(const void *str, int c, realized_size_t n) {
  char *temp = (char *)str;
  char *flag = realized_NULL;
  for (realized_size_t i = 0; flag == realized_NULL && i < n; i++)
    if (*temp++ == c) flag = temp - 1;
  return flag;
}
