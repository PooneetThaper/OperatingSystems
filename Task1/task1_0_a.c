#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main (int argc, char* argv[]) {
  char* filepath = argv[1];
  int returnval;

  /*
  // Check file existence
  returnval = access(filepath, F_OK);
  if (returnval == 0){
    printf ("\n %s exists\n", filepath);
  } else {
    if (errno == EACCES) {
      printf ("%s is not accessible\n", filepath);
    } else if (errno == ENOENT) {
      printf ("%s does not exist\n", filepath);
      return 0;
    }
  }
  */

  // Check read access
  returnval = access(filepath, R_OK);
  if (returnval != 0){
    /*
    if (errno == EACCES) {
      perror ("%s is not accessible\n", filepath);
      return 1;
    } else if (errno == ENOENT) {
      perror ("%s does not exist\n", filepath);
      return 1;
    }
    */
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
