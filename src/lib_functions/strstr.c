#include "../realized_string.h"

char *realized_strstr(const char *haystack, const char *needle) {
  char *ch = NULL;
  int flag = 0;
  char *orig_str1 = (char *)haystack;
  realized_size_t len1 = realized_strlen(haystack);
  if (realized_strlen(needle) == 0) return orig_str1;
  char *orig_str2 = (char *)needle;
  realized_size_t len2 = realized_strlen(needle);
  realized_size_t i = 0;
  realized_size_t j = 0;
  for (; i <= len1 && flag == 0; i++) {
    if (orig_str1[i] == orig_str2[j]) {
      for (j = 0; j < len2 && i + j < len1 && orig_str1[i + j] == orig_str2[j];
           j++) {
        if (j == len2 - 1) {
          flag = 1;
          ch = &orig_str1[i];
        }
      }
    }
  }
  return ch;
}
