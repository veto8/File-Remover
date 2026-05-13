#include "filelist.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For stat() or lstat()
#include <unistd.h>   // For chdir() or realpath()

int filelist(const char *path, char **list, int capacity) {

  DIR *dir;
  struct dirent *entry;
  struct stat statbuf;
  char full_path[1024]; // Buffer for full path (adjust size as needed)
  int filled = 0;
  // Open the directory
  dir = opendir(path);
  if (dir == NULL) {
    perror("Error opening directory"); // Print error message
    fprintf(stderr, "Failed to open: %s\n", path);
    return 0; // Exit the function if directory cannot be opened
  }

  list[0] = "hello";
  // Read directory entries one by one
  while ((entry = readdir(dir)) != NULL) {
    // Skip "." and ".." entries to avoid infinite loops
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    // Construct the full path to the current entry
    // snprintf is safer than strcpy/strcat for preventing buffer overflows
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    // Get file status (info like type: file, directory, symlink, etc.)
    // Use lstat to follow symlinks, stat to resolve them if needed.
    // For printing paths, lstat is usually fine.
    if (lstat(full_path, &statbuf) == -1) {
      perror("Error getting file status");
      fprintf(stderr, "Failed to get status for: %s\n", full_path);
      continue; // Skip this entry if status cannot be obtained
    }

    // Print the full path
    printf("%s\n", full_path);

    // If the entry is a directory, recurse into it
    if (S_ISDIR(statbuf.st_mode)) {
      filelist(full_path, list, capacity); // Recursive call
    }
  }

  // Close the directory
  closedir(dir);
  return filled;
}
