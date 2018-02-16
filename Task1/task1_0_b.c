#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[]){
  char* filepath = argv[1];
  int retval = open(filepath, O_RDONLY|O_CREAT);

  if (retval == 0) {
    printf ("\n created and opened %s just fine", filepath);
  } else {
    // There was an issue, writing error and returning 1
    char message[100];
    strcpy(message, filepath);
    perror(message);
    return 1;
  }

  return 0;
}
