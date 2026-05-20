#include "curl_list.h"
#include "filelist.h"
#include "list_diff.h"
#include "remove_file.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For stat() or lstat()
#include <unistd.h>   // For chdir() or realpath()

int main(int argc, char *argv[]) {
  char *folder_path = "";
  char *url = "";

  printf("... start main fun \n");

  for (int i = 0; i < argc; i++) {
    if (strncmp(argv[i], "-f", 2) == 0) {
      if (argv[i + 1]) {
        folder_path = argv[i + 1];
      }
    }

    if (strncmp(argv[i], "-u", 2) == 0) {
      if (argv[i + 1]) {
        url = argv[i + 1];
      }
    }
  }

  /********************************************************************/
  const int capacity = 1000000;
  int counter1 = 0;
  int c1 = 0;
  // char *list1[capacity];
  char **list1 = malloc(capacity * sizeof(char *));
  if (folder_path != "") {
    printf("main %s\n", folder_path);
    c1 = filelist(folder_path, list1, capacity, counter1);
    // printf("List1:  %d\n", c1);
  }

  //  for (size_t i = 0; i < c1; i++) {
  //    printf("%s\n", list1[i]);
  //}

  /*******************************************************************/

  // const char *url = "http://sapir.salamander-jewelry.net/picture_path/name";
  size_t c2;
  char **list2 = curl_list(url, &c2);
  // printf("List2:  %d \n", c2);

  /*******************************************************************/

  size_t c3;
  const char **diff =
      find_missing((const char **)list1, c1, (const char **)list2, c2, &c3);

  printf("List1:  %zu \n", c1);
  printf("List2:  %zu  \n", c2);
  printf("Diff:  %zu \n", c3);

  for (size_t i = 0; i < c3; i++) {
    int ok = remove_file(diff[i]);

    // printf("%s\n", diff[i]);
  }
}
