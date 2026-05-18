#include "curl_list.h"
#include "filelist.h"
#include "list_diff.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For stat() or lstat()
#include <unistd.h>   // For chdir() or realpath()

int main(int argc, char *argv[]) {
  char *folder_path = "";
  printf("... start main fun \n");

  for (int i = 0; i < argc; i++) {
    if (strncmp(argv[i], "-p", 2) == 0) {
      // printf("  %b\n", strncmp(argv[i], base, 2));
      if (argv[i + 1]) {
        // folder_path = sanitize_string(argv[i + 1]);
        folder_path = argv[i + 1];
      }
    }
  }

  // *******************************************************************
  // Get the first list

  const char *url = "http://sapir.salamander-jewelry.net/picture_path/name";
  size_t counter;
  const char **list1 = curl_list(url, &counter);
  printf("list1:  %dx \n", counter);
  // for (size_t i = 0; i < counter; i++) {
  //   printf("%s\n", list2[i]);
  //  }

  // *******************************************************************
  // Get the second list

  /*
  const int capacity = 1000000;
  int counter = 0;
  int c = 0;
  char *list[capacity];

  if (folder_path != "") {
    printf("main %s\n", folder_path);
    c = filelist(folder_path, list, capacity, counter);
    printf("filled  %d\n", c);
  }

  for (size_t i = 1; i < 10; i++) {
    // printf("%s\n", list[i]);
  }

  char *a[] = {"apple", "banana", "cherry", "date"};
  char *b[] = {"banana", "date", "fig"};
  size_t count;
  const char **diff = find_missing(list, c, list, c, &count);
  for (size_t i = 0; i < count; i++) {
    // printf("%s\n", diff[i]);
  }
  */
}
