#include "filelist.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For stat() or lstat()
#include <unistd.h>   // For chdir() or realpath()

const char **listdiff(const char **list1, size_t n1, const char **list2,
                      size_t n2, size_t *out_count) {
  const char **result = malloc(n1 * sizeof(char *));
  size_t count = 0;
  for (size_t i = 0; i < n1; i++) {
    int found = 0;
    for (size_t j = 0; j < n2; j++) {
      if (strcmp(list1[i], list2[j]) == 0) {
        found = 1;
        break;
      }
    }
    if (!found)
      result[count++] = list1[i];
  }
  *out_count = count;
  return result;

  /*
  Usage:
  const char *a[] = {"apple", "banana", "cherry", "date"};
  const char *b[] = {"banana", "date", "fig"};
  size_t count;
  const char **diff = find_missing(a, 4, b, 3, &count);
  // diff = {"apple", "cherry"}, count = 2
  free(diff);

  return counter;
  */
}
