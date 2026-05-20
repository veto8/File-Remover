#include "list_diff.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For stat() or lstat()
#include <unistd.h>   // For chdir() or realpath()

int ends_with(const char *str, const char *suffix) {
  size_t slen = strlen(str);
  size_t suflen = strlen(suffix);
  if (suflen > slen)
    return 0;
  return strcmp(str + slen - suflen, suffix) == 0;
}

const char **find_missing(const char **list1, size_t n1, const char **list2,
                          size_t n2, size_t *out_count) {

  const char **result = malloc(n1 * sizeof(char *));
  size_t count = 0;
  for (size_t i = 0; i < n1; i++) {
    int found = 0;
    for (size_t j = 0; j < n2; j++) {
      int endswith = (ends_with(list1[i], list2[j]));
      if (endswith == 1) {
        found = 1;
        break;
      }
    }
    if (found == 0) {
      result[count++] = strdup(list1[i]);
    }
  }
  *out_count = count;

  return result;
}
