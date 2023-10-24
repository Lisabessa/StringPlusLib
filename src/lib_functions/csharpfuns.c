#include "../realized_string.h"

void *realized_to_upper(const char *str) {
  char *new_str = realized_NULL;

  if (str != realized_NULL) {
    new_str = malloc((realized_strlen(str) + 1) * sizeof(char));
    if (new_str != realized_NULL) {
      for (int i = 0; i <= (int)realized_strlen(str); i++) {
        if (str[i] >= 97 && str[i] <= 122) {
          new_str[i] = str[i] - 32;
        } else {
          new_str[i] = str[i];
        }
      }
    }
  }

  return new_str;
}

void *realized_to_lower(const char *str) {
  char *new_str = realized_NULL;

  if (str != realized_NULL) {
    new_str = malloc((realized_strlen(str) + 1) * sizeof(char));
    if (new_str != realized_NULL) {
      for (int i = 0; i <= (int)realized_strlen(str); i++) {
        if (str[i] >= 65 && str[i] <= 90) {
          new_str[i] = str[i] + 32;
        } else {
          new_str[i] = str[i];
        }
      }
    }
  }

  return new_str;
}

void *realized_insert(const char *src, const char *str, realized_size_t start_index) {
  char *new_str = realized_NULL;
  if (src != realized_NULL && str != realized_NULL && start_index <= realized_strlen(src)) {
    new_str = malloc((realized_strlen(str) + realized_strlen(src) + 1) * sizeof(char));
    if (new_str != realized_NULL) {
      int j = 0;
      int k = (int)start_index;
      for (int i = 0; i < (int)(realized_strlen(str) + realized_strlen(src)); i++) {
        if (i >= (int)start_index &&
            i < (int)start_index + (int)realized_strlen(str)) {
          new_str[i] = str[j++];
        } else if (i < (int)start_index) {
          new_str[i] = src[i];
        } else {
          new_str[i] = src[k++];
        }
      }
      new_str[realized_strlen(str) + realized_strlen(src)] = '\0';
    }
  }
  return new_str;
}

void *realized_trim(const char *src, const char *trim_chars) {
  if (src == realized_NULL) return realized_NULL;
  if (trim_chars == realized_NULL || trim_chars[0] == '\0') {
    return realized_trim(src, " \n\t\f\v\r");
  }
  const char *start = src;
  while (*start && trim_chars != realized_NULL &&
         realized_strchr(trim_chars, *start) != realized_NULL)
    start++;
  const char *end = src + realized_strlen(src) - 1;
  while (end > start && trim_chars != realized_NULL &&
         realized_strchr(trim_chars, *end) != realized_NULL)
    end--;
  char *new_str = (char *)malloc(end - start + 2);
  realized_strncpy(new_str, start, end - start + 1);
  new_str[end - start + 1] = '\0';

  return new_str;
}
