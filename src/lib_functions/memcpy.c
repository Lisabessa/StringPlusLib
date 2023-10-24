#include "../realized_string.h"

void *realized_memcpy(void *dest, const void *src, realized_size_t n) {
  char *temp = (char *)dest;
  char *temp1 = (char *)src;
  for (realized_size_t i = 0; i < n; i++) temp[i] = *temp1++;
  return temp;
}
