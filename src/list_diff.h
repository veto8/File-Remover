#ifndef LIB_H2
#define LIB_H2
#include <stddef.h>

const char **find_missing(const char **list1, size_t n1, const char **list2,
                          size_t n2, size_t *out_count);

#endif
