#include "../realized_string.h"

void *realized_memset(void *str, int c, realized_size_t n) {
  char *temp = (char *)str;
  for (realized_size_t i = 0; i < n; i++) temp[i] = c;
  return temp;
}
