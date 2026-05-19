#include "filelist.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int filelist(const char *path, char **list, int capacity, int counter) {

  // printf("%d\n", counter);

  DIR *dir;
  struct dirent *entry;
  struct stat statbuf;
  char full_path[1024];

  dir = opendir(path);
  if (dir == NULL) {
    perror("Error opening directory"); // Print error message
    fprintf(stderr, "Failed to open: %s\n", path);
    return 0; // Exit the function if directory cannot be opened
  }

  while ((entry = readdir(dir)) != NULL) {

    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    if (lstat(full_path, &statbuf) == -1) {
      perror("Error getting file status");
      fprintf(stderr, "Failed to get status for: %s\n", full_path);
      continue;
    }

    if (S_ISDIR(statbuf.st_mode)) {
      counter = filelist(full_path, list, capacity, counter); // Recursive call
    } else {
      // printf("%d\n", counter);
      // printf("%s\n", full_path);
      list[counter] = strdup(full_path);
      counter++;
    }
  }

  closedir(dir);

  return counter;
}
