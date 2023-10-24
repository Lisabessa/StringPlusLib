#include "../realized_string.h"

char *realized_strchr(const char *str, int c) {
  char *ch = NULL;
  char *orig_str = (char *)str;
  int flag = 0;
  realized_size_t len = realized_strlen(str);
  for (realized_size_t i = 0; i <= len && flag != 1; i++) {
    if (orig_str[i] == c) {
      flag = 1;
      ch = &orig_str[i];
    }
  }

  return ch;
}
