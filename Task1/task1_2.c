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

  // Open the source file for reading only using the open system call
  int source_file = open(source_filepath, O_RDONLY);

  //NOTE: The approach taken in this program is to read the whole source file into a dynamic buffer then write the buffer to the destination file in one shot. This may not be the best idea for larger files.

  // Allocate a char array of reasonable size as a buffer for reading in one character at a time
  int capacity = 20;
  int size = 0;
  char* buffer= malloc(capacity);

  // Read character by character while able to do so using the read system command
  while (read(source_file, &buffer[size++], 1)) {
    // Read 1 byte (one character) from source file to buffer and increment the size of the buffer

    // If size == capacity (buffer full), reallocate larger buffer
    if (size == capacity) {
      char* new_buffer = realloc(buffer, capacity*2);
      if(!new_buffer){
        // If reallocating the buffer fails, terminate program
        printf(stderr, "Issue reallocating buffer");
        return 1;
      }
      buffer = new_buffer;
      capacity *= 2;
    }

  }

  // Close source file using close system call
  close(source_file);

  // Open destination file for writing only using open system call. If it does not exist, create it with read and write permissions.
  int destination_file = open(destination_filepath, O_WRONLY | O_CREAT, 0666);

  // Write buffer into destination file using write system call
  write(destination_file, buffer, size);

  // Close destination file
  close(destination_file);

  free(buffer);
  return 0;
}
