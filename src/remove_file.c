#include "remove_file.h"
#include "filelist.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int remove_file(const char *path) {
  int ok = 0;

  if (remove(path) == 0) {
    printf("Deleted %s\n", path);
    ok = 1;
  } else {
    perror("Error deleting file");
    ok = 0;
  }
  return ok;
}
