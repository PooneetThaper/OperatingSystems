#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
  char* filepath = argv[1];

  // Check read access and existance of file
  int returnval = access(filepath, R_OK);
  if (returnval != 0){
    // There was an issue, writing error and returning 1
    char message[100];
    strcpy(message, filepath);
    perror(message);
    return 1;
  }

  // Open the file for reading only using the open system call
  int file = open(filepath, O_RDONLY);

  // Allocate a char array as a buffer for reading in one character at a time
  char buffer[1];

  printf("\n");

  // Read character by character while able to do so using the read system command
  while(read(file, buffer, 1)) {
    // Read 1 byte (one character) from file to buffer
    printf("%c", buffer[0]);
    // Print character to terminal
  }

  printf("\n");

  close(file);

  return 0;
}
