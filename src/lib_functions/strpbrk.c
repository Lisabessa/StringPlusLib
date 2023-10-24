#include "../realized_string.h"

char *realized_strpbrk(const char *str1, const char *str2) {
  char *ch = NULL;
  char *orig_str1 = (char *)str1;
  char *orig_str2 = (char *)str2;
  int flag = 0;
  realized_size_t len1 = realized_strlen(str1);
  for (realized_size_t i = 0; i < len1 && flag == 0; i++) {
    if (realized_strchr(orig_str2, orig_str1[i]) != NULL) {
      flag = 1;
      ch = &orig_str1[i];
    }
  }

  return ch;
}
