#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main (int argc, char* argv[]) {
  char* filepath = argv[1];
  int returnval;

  // Check read access
  returnval = access(filepath, R_OK);
  if (returnval != 0){
    // There was an issue, writing error and returning 1
    char message[100];
    strcpy(message, filepath);
    perror(message);
    return 1;
  }

  // Check read access ...
  returnval = access(filepath, R_OK);
  if (returnval == 0){
    printf("\n %s is readable \n", filepath);
  } else {
    // There was an issue, writing error and returning 1
    char message[100];
    strcpy(message, filepath);
    perror(message);
    return 1;
  }

  // Check write access ...
  returnval = access(filepath, W_OK);
  if (returnval == 0){
    printf("\n %s is writeable \n", filepath);
  } else {
    // There was an issue, writing error and returning 1
    char message[100];
    strcpy(message, filepath);
    perror(message);
    return 1;
  }

  return 0;
}
