#include "../realized_string.h"

char *realized_strncat(char *dest, const char *src, realized_size_t n) {
  realized_size_t len1 = realized_strlen(dest);
  realized_size_t len2 = realized_strlen(src);
  realized_size_t i = 0;
  for (i = 0; i <= len2 && i < n; i++) {
    dest[len1 + i] = src[i];
  }
  return dest;
}
