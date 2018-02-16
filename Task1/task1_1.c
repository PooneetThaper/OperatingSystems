#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char* argv[]){
  char* filepath = argv[1];
  int returnval;

  // Check read access and existance of file
  returnval = access(filepath, R_OK);
  if (returnval != 0){
    if (errno == EACCES) {
      printf ("%s is not accessible\n", filepath);
    } else if (errno == ENOENT) {
      printf ("%s does not exist\n", filepath);
      return 0;
    }
  }

  // Read into a char buffer and append to vector
  int file = open(filepath, O_RDONLY);
  char buffer[1];

  printf("\n");
  while(read(file, buffer, 1)) {
    printf("%c", buffer[0]);
  }
  printf("\n");

  return 0;
}
