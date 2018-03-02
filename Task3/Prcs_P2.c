#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
  // It is assumed that this file compiled as follows
  // gcc Prcs_P2 -o P2

  char* source_filepath = "source.txt";
  char* destination_filepath1 = "destination1.txt";
  char* destination_filepath2 = "destination2.txt";
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
  int source_file = open(source_filepath, O_RDONLY);

  // Check write access and existance of destination file
  returnval = access(destination_filepath1, W_OK);
  if (returnval != 0){
    if (errno == EACCES) {
      // There was an issue, writing error and returning 1
      char message[100];
      strcpy(message, destination_filepath1);
      perror(message);
      return 1;
    }
  }
  int destination_file1 = open(destination_filepath1, O_WRONLY);

  // Check write access and existance of destination file
  returnval = access(destination_filepath2, W_OK);
  if (returnval != 0){
    if (errno == EACCES) {
      // There was an issue, writing error and returning 1
      char message[100];
      strcpy(message, destination_filepath2);
      perror(message);
      return 1;
    }
  }
  int destination_file2 = open(destination_filepath2, O_WRONLY);

  char* buffer= malloc(100);
  int contin = 1; // Pseudo-boolean to determine if the buffer was filled in the last iteration of the loop
  int dest_1 = 1; // Pseudo-boolean to switch between the destinations

  // Read in 100 bytes while able to do so using the read system command
  while (contin) {
    contin = 0;
    if (dest_1) {
      int size = read(source_file, &buffer[0], 100);
      for (int i = 0; i< size ; i++) {
        if (buffer[i] == '1'){
          buffer[i] = 'A';
        }
      }
      write(destination_file1, buffer, 100);
      if (size == 100) {
        contin = 1;
        dest_1 = 0;
      }

    } else {
      int size = read(source_file, &buffer[0], 50);
      for (int i = 0; i< size ; i++) {
        if (buffer[i] == '2'){
          buffer[i] = 'B';
        }
      }
      write(destination_file2, buffer, 50);
      if (size == 50) {
        contin = 1;
        dest_1 = 1;
      }
    }
  }

  close(source_file);
  close(destination_file1);
  close(destination_file2);
  return 0;
}
