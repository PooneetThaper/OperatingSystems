#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[]){
  // It is assumed that this file compiled as follows
  // gcc Prcs_P1 -o P1

  int destination1 = open("destination1.txt", O_CREAT, 0777);
  close(destination1);
  int destination2 = open("destination2.txt", O_CREAT, 0777);
  close(destination2);
  return 0;
}
