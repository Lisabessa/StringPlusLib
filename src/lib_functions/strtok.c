#include "../realized_string.h"

char *realized_strtok(char *str, const char *delim) {
  static char *last;
  char *tok;
  if (str == realized_NULL && (str = last) == realized_NULL) return realized_NULL;
  char *spoon;
  char c, sc;
  int k = 0;
  do {
    k++;
    c = *str++;
    for (spoon = (char *)delim; (sc = *spoon++) != 0 && (c != sc);)
      ;
  } while ((c == sc) && c != 0);
  if (c == 0) {
    last = realized_NULL;
    return realized_NULL;
  }
  tok = str - 1;
  do {
    c = *str++;
    spoon = (char *)delim;
    do {
      sc = *spoon++;
      if (sc == c) {
        if (c == 0)
          str = realized_NULL;
        else
          str[-1] = 0;
        last = str;
        return tok;
      }
    } while (sc != 0);
  } while (1);
}
