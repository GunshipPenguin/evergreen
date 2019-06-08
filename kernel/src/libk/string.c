#include "libk/string.h"

size_t strnlen(const char *str, size_t maxlen) {
  size_t len = 0;

  while (str[len] != '\0' && len < maxlen) {
    len++;
  }

  return len;
}

size_t strlen(const char* str) {
  size_t len = 0;
  while (str[len]) {
    len++;
  }

  return len;
}

