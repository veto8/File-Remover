#include "filelist.h"
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

  const int capacity = 1000000;
  int counter = 0;
  int filled = 0;
  char *list[capacity];

  if (folder_path != "") {
    printf("main %s\n", folder_path);
    filled = filelist(folder_path, list, capacity, counter);
    printf("filled  %d\n", filled);
  }
}
