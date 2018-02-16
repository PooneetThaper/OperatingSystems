#include <stdio.h>
#include <unistd.h>
#include <errno.h>

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
    if (errno == EACCES) {
      printf ("%s is not accessible\n", filepath);
    } else if (errno == ENOENT) {
      printf ("%s does not exist\n", filepath);
      return 0;
    }
  }

  // Check read access ...
  returnval = access(filepath, R_OK);
  if (returnval == 0){
    printf ("\n %s is readable \n", filepath);
  } else {
    printf ("\n error %d encountered \n", errno);
    if (errno == EACCES) {
      printf ("\ncant access \n");
    }
  }

  // Check write access ...
  returnval = access(filepath, W_OK);
  if (returnval == 0){
    printf ("\n %s is writeable \n", filepath);
  } else {
    printf ("\n error %d encountered \n", errno);
  }

  return 0;
}
