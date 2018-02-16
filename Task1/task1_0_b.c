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
    printf ("\n got error no %d and retval %d\n", errno, retval);
  }

  return 0;
}
