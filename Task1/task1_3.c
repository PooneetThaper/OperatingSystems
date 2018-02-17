#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
  char* source_filepath = argv[1];
  char* destination_filepath = argv[2];
  int returnval;

  // Check read access and existance of source file
  returnval = access(source_filepath, R_OK);
  if (returnval != 0){
    // There was an issue, writing error and returning 1
    char message[100];
    strcpy(message, source_filepath);
    perror(message);
    return 1;
  }

  // Check write access and existance of destination file
  returnval = access(destination_filepath, W_OK);
  if (returnval != 0){
    if (errno == EACCES) {
      // There was an issue, writing error and returning 1
      char message[100];
      strcpy(message, destination_filepath);
      perror(message);
      return 1;
    }
  }

  // Open the source and destination files for reading only and writing only, respectively, using the open system call
  int source_file = open(source_filepath, O_RDONLY);
  int destination_file = open(destination_filepath, O_WRONLY | O_CREAT, 0666);

  // Allocate a char array of size 100 as a buffer for reading in 100 characters at a time
  char* buffer= malloc(103);
  int size = 100;
  buffer[100] = 'X';
  buffer[101] = 'Y';
  buffer[102] = 'Z';

  // Read in 100 bytes while able to do so using the read system command
  while (size >= 100) {
    size = read(source_file, &buffer[0], 100);

    for (int i = 0; i< size ; i++) {
      if (buffer[i] == '1'){
        buffer[i] = 'A';
      }
    }

    // Write buffer into destination file using write system call
    if (size == 100){
      write(destination_file, buffer, 103);
    } else {
      write(destination_file, buffer, size);
    }

  }

  write(destination_file, "\n", 1);

  // Close source and destination files
  close(source_file);
  close(destination_file);

  free(buffer);

  return 0;
}
