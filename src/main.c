#include "lib.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For stat() or lstat()
#include <unistd.h>   // For chdir() or realpath()

void list_directory_recursive(const char *path) {
  DIR *dir;
  struct dirent *entry;
  struct stat statbuf;
  char full_path[1024]; // Buffer for full path (adjust size as needed)

  // Open the directory
  dir = opendir(path);
  if (dir == NULL) {
    perror("Error opening directory"); // Print error message
    fprintf(stderr, "Failed to open: %s\n", path);
    return; // Exit the function if directory cannot be opened
  }

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
      list_directory_recursive(full_path); // Recursive call
    }
  }

  // Close the directory
  closedir(dir);
}

int main(int argc, char *argv[]) {
  char *folder_path = "";
  printf("main\n");

  for (int i = 0; i < argc; i++) {
    if (strncmp(argv[i], "-p", 2) == 0) {
      // printf("  %b\n", strncmp(argv[i], base, 2));
      if (argv[i + 1]) {
        if (file_exists(argv[i + 1])) {
          folder_path = sanitize_string(argv[i + 1]);
        }
      }
    }
  }

  const int MAX_STRINGS = 1000000000;
  const char *path[MAX_STRINGS];

  if (folder_path != "") {
    printf("main %s\n", folder_path);
    //    list_directory_recursive(folder_path);
  }
}
