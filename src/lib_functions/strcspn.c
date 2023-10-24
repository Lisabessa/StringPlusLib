#include "../realized_string.h"

realized_size_t realized_strcspn(const char *str1, const char *str2) {
  realized_size_t ln = 0;
  int flag = 1;
  char c, s;
  char *temp1 = (char *)str1;
  char *temp2 = (char *)str2;
  s = *temp2++;
  while ((c = *temp1++) != 0 && c != s && flag) {
    temp2 = (char *)str2;
    flag = 1;
    while (flag && (s = *temp2++) != 0) {
      if (c == s) flag = 0;
    }
    if (flag) ln++;
  }
  return ln;
}
