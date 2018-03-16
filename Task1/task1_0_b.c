/* Task 1 Part 0b
Complilation: gcc task1_0_b.c -o create_open
Usage: ./create_open [destination_filepath]
*/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  char* filepath = argv[1];
  int file = open(filepath, O_RDONLY | O_CREAT, 0666);

  if (file > 0) {
    printf ("\n created and opened %s just fine\n", filepath);
  } else {
    // There was an issue, writing error and returning 1
    char message[100];
    strcpy(message, filepath);
    perror(message);
    return 1;
  }

  close(file);

  return 0;
}
