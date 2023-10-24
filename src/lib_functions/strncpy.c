#include "../realized_string.h"

char *realized_strncpy(char *dest, const char *src, realized_size_t n) {
  // realized_size_t len1 = realized_strlen(dest);
  realized_size_t len2 = realized_strlen(src);
  realized_size_t i = 0;
  for (i = 0; i < n; i++) {
    if (i > len2 - 1)
      dest[i] = '\0';
    else
      dest[i] = src[i];
  }
  return dest;
}
