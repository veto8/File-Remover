#include "curl_list.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For stat() or lstat()
#include <unistd.h>   // For chdir() or realpath()

static size_t write_memory_callback(void *contents, size_t size, size_t nmemb,
                                    void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if (ptr == NULL) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

const char **curl_list(const char *url, size_t *counter) {
  printf("%s\n", url);
  size_t count = 0;
  const char **result = malloc(10000 * sizeof(char *));

  char *translation = NULL;

  CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;
  chunk.memory = NULL;

  chunk.size = 0;
  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
      goto cleanup;
    } else {

      json_error_t error;
      json_t *root = json_loads(chunk.memory, 0, &error);

      if (!root) {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        goto cleanup;
      } else {

        // json_t *translated_text = json_object_get(root);
        size_t len = json_array_size(root);
        for (size_t i = 0; i < len; i++) {
          json_t *elem = json_array_get(root, i);
          const char *str = json_string_value(elem);
          // printf("%s\n", str);
          result[i] = str;
          count++;
        }

      cleanup_json:
        json_decref(root);
      }
    }

  cleanup:
    // Clean up curl
    curl_easy_cleanup(curl);
  } else {
    fprintf(stderr, "curl_easy_init() failed\n");
    translation = NULL;
  }

  free(chunk.memory);

  // char url[256]; // Adjust size as needed

  /*
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
  */
  *counter = count;
  return result;
}
