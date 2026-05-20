#ifndef LIB_H3
#define LIB_H3

#include <ctype.h>
#include <curl/curl.h>
#include <dirent.h>
#include <errno.h>
#include <jansson.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include <stddef.h>

// Structure to hold the response data
struct MemoryStruct {
  char *memory;
  size_t size;
};

char **curl_list(const char *url, size_t *counter);

#endif
