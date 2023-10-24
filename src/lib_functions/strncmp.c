#include "../realized_string.h"

int realized_strncmp(const char *str1, const char *str2, realized_size_t n) {
  realized_size_t len1 = realized_strlen(str1);
  realized_size_t len2 = realized_strlen(str2);
  int flag = 0;
  int out = 0;
  realized_size_t i = 0;
  for (; i <= len1 && i <= len2 && i < n && flag == 0; i++) {
    if (str1[i] != str2[i]) {
      flag = 1;
      out = str1[i] - str2[i];
    }
  }
  return out;
}