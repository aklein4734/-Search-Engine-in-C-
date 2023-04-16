#include <stdio.h>    // for snprintf
#include <stdlib.h>   // for EXIT_SUCCESS, NULL
#include <string.h>   // for strrchr, strcmp, strlen
#include <stdbool.h>  // for bool
#include <dirent.h> 
#include <sys/types.h>
#include <errno.h>

#include "ro_file.h"


/*** HELPER FUNCTION DECLARATIONS ******************************************/

// Returns whether or not a filename ends in ".txt".
bool IsTxtFile(char* filename);

// Concatenate the directory and file names into a full path. The caller is
// responsible for freeing the allocated string. Exits if an error occurs.
char* Concatenate(char* dirname, char* filename);


/*
 * This program:
 * - Accepts a directory name as a command-line argument.
 * - Scans through the directory looking for all files whose names end with
 *   the four characters ".txt".
 * - For every such file found, write the contents of those files to stdout
 *   without adding any additional characters or formatting.
 *   Eventually reading the files with ro_file module.
 */
int main(int argc, char** argv) {
  // TODO: Write this function
  if (argc != 2) {  // checks for if exactly 1 paramiter was passed in
    fprintf(stderr, "ERROR: incorect number of inputs\n");
    return EXIT_FAILURE;
  }
  errno = 0;
  DIR *dir = opendir(argv[1]);
  if (errno != 0) {
    fprintf(stderr, "Incorect file path passed in\n");
  }
  while (dir && errno == 0) {
    struct dirent *help = readdir(dir);
    if (help == NULL){
      break;
    }
    if (IsTxtFile(help->d_name)) {
      FILE *file = fopen(Concatenate(argv[1], help->d_name), "r");
      if (file == NULL) {
        printf("wrong");
      }
      char buf[100];
      while (!feof(file)) {
        if (fgets(buf , 100 , file) == NULL) {
          break;
        }
        fputs(buf, stdout);
      }
      fclose(file);
    }
  }
  closedir(dir);
  
  return EXIT_SUCCESS;
}


/*** HELPER FUNCTION DEFINITIONS *******************************************/

bool IsTxtFile(char* filename) {
  char* dot = strrchr(filename, '.');
  return dot && !strcmp(dot, ".txt");
}

char* Concatenate(char* dirname, char* filename) {
  bool has_trailing_slash = dirname[strlen(dirname) - 1] == '/';
  // Concatenate directory and file name.
  size_t dlen = strlen(dirname);
  size_t flen = strlen(filename);
  // Malloc space for full path name:
  // dlen + strlen("/") + flen + strlen('\0') = dlen + flen + 2
  int size_to_malloc = has_trailing_slash ? dlen + flen + 1 : dlen + flen + 2;
  char* fullpath = (char*) malloc(sizeof(char) * (size_to_malloc));
  if (fullpath == NULL) {
    fprintf(stderr, "Error on malloc.\n");
    exit(EXIT_FAILURE);
  }
  if (has_trailing_slash) {
    snprintf(fullpath, size_to_malloc, "%s%s", dirname, filename);
  } else {
    snprintf(fullpath, size_to_malloc, "%s/%s", dirname, filename);
  }
  return fullpath;
}
