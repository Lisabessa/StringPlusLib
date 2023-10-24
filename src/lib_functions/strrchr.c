#include "../realized_string.h"

char *realized_strrchr(const char *str, int c) {
  char *ch = NULL;
  char *orig_str = (char *)str;
  realized_size_t len = realized_strlen(str);
  for (realized_size_t i = 0; i <= len; i++) {
    if (orig_str[i] == c) {
      ch = &orig_str[i];
    }
  }

  return ch;
}
