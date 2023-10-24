#include "../realized_string.h"

int realized_memcmp(const void *str1, const void *str2, realized_size_t n) {
  char *temp1 = (char *)str1;
  char *temp2 = (char *)str2;
  int flag = 0;
  for (realized_size_t i = 0; flag == 0 && i < n; i++)
    if (temp1[i] - temp2[i] != 0) flag = temp1[i] - temp2[i];
  return flag;
}