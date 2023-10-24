#include "../realized_string.h"
#include "auxiliary_functions.h"

struct SscanfFlags {
  char spec;
  realized_size_t width;
  char length;
  int double_length;
  int supressor;
};

void parse_specifiers_sscanf(struct SscanfFlags *flags, const char **p) {
  (*p)++;

  if (**p == '*') {
    flags->supressor = 1;
    (*p)++;
  }
  while (is_digit(**p)) {
    flags->width = flags->width * 10 + (**p - '0');
    (*p)++;
  }
  if (**p == 'h' || **p == 'l' || **p == 'L') {
    flags->length = **p;
    (*p)++;
    if (flags->length == **p) {
      flags->double_length = 1;
      (*p)++;
    }
  }

  if (**p == 'c' || **p == 'd' || **p == 'i' || **p == 'e' || **p == 'E' ||
      **p == 'g' || **p == 'G' || **p == 'f' || **p == 'o' || **p == 's' ||
      **p == 'u' || **p == 'x' || **p == 'X' || **p == 'p' || **p == 'n' ||
      **p == '%') {
    flags->spec = **p;
  }
}

void assign_int_value(struct SscanfFlags flags, va_list *args,
                      long long value) {
  if (!flags.double_length) {
    switch (flags.length) {
      case 'l': {
        long *l_value;
        l_value = va_arg(*args, long *);
        *l_value = (long)value;
        break;
      }
      case 'h': {
        short *h_value;
        h_value = va_arg(*args, short *);
        *h_value = (short)value;
        break;
      }
      default: {
        int *p_value;
        p_value = va_arg(*args, int *);
        *p_value = (int)value;
        break;
      }
    }
  } else {
    switch (flags.length) {
      case 'l': {
        long long *l_value;
        l_value = va_arg(*args, long long *);
        *l_value = value;
        break;
      }
      case 'h': {
        signed char *h_value;
        h_value = va_arg(*args, signed char *);
        *h_value = (signed char)value;
        break;
      }
    }
  }
}

void assign_uint_value(struct SscanfFlags flags, va_list *args,
                       unsigned long long value) {
  if (!flags.double_length) {
    switch (flags.length) {
      case 'l': {
        unsigned long *l_value;
        l_value = va_arg(*args, unsigned long *);
        *l_value = (unsigned long)value;
        break;
      }
      case 'h': {
        unsigned short *h_value;
        h_value = va_arg(*args, unsigned short *);
        *h_value = (unsigned short)value;
        break;
      }
      default: {
        unsigned int *p_value;
        p_value = va_arg(*args, unsigned int *);
        *p_value = (unsigned int)value;
        break;
      }
    }
  } else {
    switch (flags.length) {
      case 'l': {
        unsigned long long *l_value;
        l_value = va_arg(*args, unsigned long long *);
        *l_value = value;
        break;
      }
      case 'h': {
        unsigned char *h_value;
        h_value = va_arg(*args, unsigned char *);
        *h_value = (unsigned char)value;
        break;
      }
    }
  }
}

void assign_float_value(struct SscanfFlags flags, va_list *args,
                        long double value) {
  if (flags.length == 'L') {
    long double *ld_value = va_arg(*args, long double *);
    *ld_value = value;
  } else if (flags.length == 'l') {
    double *d_value = va_arg(*args, double *);
    *d_value = (double)value;
  } else {
    float *p_value = va_arg(*args, float *);
    *p_value = (float)value;
  }
}

void ignore_chars(struct SscanfFlags flags, const char **p) {
  int is_str = flags.spec == 's';
  int is_wide = flags.length == 'l' || flags.length == 'L';

  do {
    if (is_wide) {
      realized_size_t n = mbrtowc(realized_NULL, *p, MB_CUR_MAX, realized_NULL);
      (*p) += n;
    } else {
      (*p)++;
    }
  } while (**p != '\0' && ((is_str) ? is_space(**p) : 0));
}

void assign_chars(struct SscanfFlags flags, va_list *args, const char **p) {
  int is_str = flags.spec == 's';
  realized_size_t width = flags.width;
  if (!is_str && width == 0) width = 1;

  char *c = va_arg(*args, char *);
  realized_size_t i = 0;
  for (; (i < width || width == 0) && ((is_str) ? !is_space(**p) : 1) &&
         **p != '\0';
       i++) {
    *c++ = **p;
    (*p)++;
  }
  if (is_str) {
    *c-- = '\0';
  }
}

void assign_wide_chars(struct SscanfFlags flags, va_list *args,
                       const char **p) {
  int is_str = flags.spec == 's';
  realized_size_t width = flags.width;
  if (!is_str && width == 0) width = 1;

  wchar_t *c = va_arg(*args, wchar_t *);
  realized_size_t i = 0;
  for (; (i < width || width == 0) && ((is_str) ? is_space(**p) : 1) &&
         **p != '\0';
       i++) {
    realized_size_t n = mbrtowc(c++, *p, MB_CUR_MAX, realized_NULL);
    (*p) += n;
  }
  if (is_str) {
    *c-- = '\0';
  }
}

int doi_specifiers(struct SscanfFlags flags, va_list *args, int base,
                   const char **p) {
  if (**p == '\0') return 0;
  long long value = 0;
  int res = str_to_int(p, &value, flags.width, base);
  if (res && !flags.supressor) {
    assign_int_value(flags, args, value);
  }
  return res;
}

int ux_specifiers(struct SscanfFlags flags, va_list *args, int base,
                  const char **p) {
  if (**p == '\0') return 0;
  unsigned long long value = 0;
  int res = str_to_uint(p, &value, flags.width, base);
  if (res && !flags.supressor) {
    assign_uint_value(flags, args, value);
  }
  return res;
}

int fge_specifiers(struct SscanfFlags flags, va_list *args, const char **p) {
  if (**p == '\0') return 0;
  long double value = 0;
  int res = str_to_float(p, &value, flags.width);
  if (res && !flags.supressor) {
    assign_float_value(flags, args, value);
  }
  return res;
}

int n_specifiers(struct SscanfFlags flags, va_list *args, realized_size_t count) {
  assign_int_value(flags, args, count);
  return 1;
}

int p_specifiers(struct SscanfFlags flags, va_list *args, const char **p) {
  if (**p == '\0') return 0;
  unsigned long long value = 0;
  int res = str_to_uint(p, &value, flags.width, 16);
  if (res && !flags.supressor) {
    void **p_value = va_arg(*args, void **);
    *p_value = (void *)value;
  }
  return res;
}

int cs_specifiers(struct SscanfFlags flags, va_list *args, const char **p) {
  if (**p == '\0') return 0;
  if (flags.spec == 's') {
    while (is_space(**p)) {
      (*p)++;
    }
  }
  if (flags.supressor) {
    ignore_chars(flags, p);
  } else {
    if (flags.length == 'l' || flags.length == 'L') {
      assign_wide_chars(flags, args, p);
    } else {
      assign_chars(flags, args, p);
    }
  }
  return 1;
}

int process_specifiers_sscanf(struct SscanfFlags flags, va_list *args,
                              const char **p, const char **str, int *count) {
  int res = 1;
  switch (flags.spec) {
    case 'd':
      res = doi_specifiers(flags, args, 10, p);
      break;
    case 'i':
      res = doi_specifiers(flags, args, 0, p);
      break;
    case 'o':
      res = doi_specifiers(flags, args, 8, p);
      break;
    case 'u':
      res = ux_specifiers(flags, args, 10, p);
      break;
    case 'x':
    case 'X':
      res = ux_specifiers(flags, args, 16, p);
      break;
    case 'f':
    case 'g':
    case 'G':
    case 'e':
    case 'E':
      res = fge_specifiers(flags, args, p);
      break;
    case 'n':
      n_specifiers(flags, args, *p - *str);
      break;
    case 'p':
      res = p_specifiers(flags, args, p);
      break;
    case 'c':
    case 's':
      res = cs_specifiers(flags, args, p);
      break;
    case '%':
      (*p)++;
      break;
    default:
      res = 0;
      break;
  }
  *count += res && !flags.supressor && flags.spec != 'n' && flags.spec != '%';
  return res;
}

int realized_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int count = 0;
  const char *pstr = str;
  int res = 1;

  for (const char *p = format; *p != '\0' && res; ++p) {
    struct SscanfFlags flags = {0};
    if (*p == '%') {
      parse_specifiers_sscanf(&flags, &p);
      res = process_specifiers_sscanf(flags, &args, &pstr, &str, &count);
    } else if (is_space(*p)) {
      while (is_space(*pstr)) {
        pstr++;
      }
    } else {
      if (*p != *pstr) {
        res = 0;
      }
      pstr++;
    }
  }

  va_end(args);
  return count;
}