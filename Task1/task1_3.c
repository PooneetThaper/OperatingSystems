#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  char* source_filepath = argv[1];
  char* destination_filepath = argv[2];

  // Check read access and existance of source file
  int returnval = access(source_filepath, R_OK);
  if (returnval != 0){
    // There was an issue, writing error and returning 1
    char message[100];
    strcpy(message, filepath);
    perror(message);
    return 1;
  }

  // Open the source and destination files for reading only and writing only, respectively, using the open system call
  int source_file = open(source_filepath, O_RDONLY);
  int destination_file = open(destination_filepath, O_WRONLY | O_CREAT, 0666);

  // Allocate a char array of size 100 as a buffer for reading in 100 characters at a time
  char (*buffer)[100];
  int size = 100;

  // Read in 100 bytes while able to do so using the read system command
  while (size == 100) {
    size = 0;

    while (read(source_file, &buffer[size], 1)) {
      if ((*buffer)[size] == '1'){
        (*buffer)[size] = 'A';
      }
      size++;
    }

    // Write buffer into destination file using write system call
    write(destination_file, buffer, size);

    // Write 'XYZ' to file
    write(destination_file, 'XYZ', 3);

  }

  // Close source and destination files
  close(source_file);
  close(destination_file);

  free(buffer);
  return 0;
}
