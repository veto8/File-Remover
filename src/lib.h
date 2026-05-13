#ifndef LIB_H
#define LIB_H

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

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <windows.h>
#define access _access
#define F_OK 0
#define mkdir(path, mode) _mkdir(path)
#else
#include <unistd.h>
#endif

#define MAX_LINE_LENGTH 256
#define MAX_MESSAGE_ID_LENGTH 64
#define MAX_MESSAGE_VALUE_LENGTH 256

struct MemoryStruct {
  char *memory;
  size_t size;
};

typedef struct {
  char **strings;
  int count;
} StringList;

int add(int a, int b);
char *sanitize_string(const char *input);
static size_t write_memory_callback(void *contents, size_t size, size_t nmemb,
                                    void *userp);
bool starts_with(const char *str, const char *prefix);
char *get_substring(const char *str, int start, int length);
void log_message(const char *filename, const char *format, ...);
char *find_first_file_with_extension(const char *directory,
                                     const char *extension);
int file_exists(const char *filename);
int create_directory(const char *directory_name);
char *concat_strings(const char *str1, const char *str2);
void trim(char *str);

int is_safe_utf8(unsigned char c);
char *url_encode_utf8(const char *str);

#endif
