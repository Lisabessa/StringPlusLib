#include "../realized_string.h"

realized_size_t realized_strlen(const char *str) {
  // original strlen gets segfault if str = NULL
  // if (str == NULL) return 0;
  realized_size_t len = 0;
  for (; str[len] != '\0'; len++)
    ;
  return len;
}
