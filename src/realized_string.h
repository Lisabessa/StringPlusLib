#ifndef realized_STRING
#define realized_STRING

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

// This is the unsigned integral type and is the result of the sizeof keyword.
#define realized_size_t unsigned long long

// This macro is the value of a null pointer constant.
#define realized_NULL (void *)0

// Searches for the first occurrence of the character c (an unsigned char) in
// the first n bytes of the string pointed to, by the argument str.
void *realized_memchr(const void *str, int c, realized_size_t n);

// Compares the first n bytes of str1 and str2.
int realized_memcmp(const void *str1, const void *str2, realized_size_t n);

// Copies n characters from src to dest.
void *realized_memcpy(void *dest, const void *src, realized_size_t n);

// Copies the character c (an unsigned char) to the first n characters of the
// string pointed to, by the argument str.
void *realized_memset(void *str, int c, realized_size_t n);

// Appends the string pointed to, by src to the end of the string pointed to, by
// dest up to n characters long.
char *realized_strncat(char *dest, const char *src, realized_size_t n);

// Searches for the first occurrence of the character c (an unsigned char) in
// the string pointed to, by the argument str.
char *realized_strchr(const char *str, int c);

// Compares at most the first n bytes of str1 and str2.
int realized_strncmp(const char *str1, const char *str2, realized_size_t n);

// Copies up to n characters from the string pointed to, by src to dest.
char *realized_strncpy(char *dest, const char *src, realized_size_t n);

// Calculates the length of the initial segment of str1 which consists entirely
// of characters not in str2.
realized_size_t realized_strcspn(const char *str1, const char *str2);

// Searches an internal array for the error number errnum and returns a pointer
// to an error message string. You need to declare macros containing arrays of
// error messages for mac and linux operating systems. Error descriptions are
// available in the original library. Checking the current OS is carried out
// using directives.
char *realized_strerror(int errnum);

// Computes the length of the string str up to but not including the terminating
// null character.
realized_size_t realized_strlen(const char *str);

// Finds the first character in the string str1 that matches any character
// specified in str2.
char *realized_strpbrk(const char *str1, const char *str2);

// Searches for the last occurrence of the character c (an unsigned char) in the
// string pointed to by the argument str.
char *realized_strrchr(const char *str, int c);

// Finds the first occurrence of the entire string needle (not including the
// terminating null character) which appears in the string haystack.
char *realized_strstr(const char *haystack, const char *needle);

// Breaks string str into a series of tokens separated by delim.
char *realized_strtok(char *str, const char *delim);

// Returns a copy of string (str) converted to uppercase. In case of any error,
// return NULL
void *realized_to_upper(const char *str);

// Returns a copy of string (str) converted to lowercase. In case of any error,
// return NULL
void *realized_to_lower(const char *str);

// Returns a new string in which a specified string (str) is inserted at a
// specified index position (start_index) in the given string (src). In case of
// any error, return NULL
void *realized_insert(const char *src, const char *str, realized_size_t start_index);

// Returns a new string in which all leading and trailing occurrences of a set
// of specified characters (trim_chars) from the given string (src) are removed.
// In case of any error, return NULL
void *realized_trim(const char *src, const char *trim_chars);

// Sends formatted output to a string pointed to, by str.
int realized_sprintf(char *str, const char *format, ...);

// Reads formatted input from a string.
int realized_sscanf(const char *str, const char *format, ...);

#endif