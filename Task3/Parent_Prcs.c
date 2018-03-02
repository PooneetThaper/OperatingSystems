#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  // It is assumed that the child Processes are compiled as follows
  // gcc Prcs_P1 -o P1
  // gcc Prcs_P2 -o P2

  int child_P1 = fork();
  int status;
  if (child_P1==0) {
    printf("Child 1");
    execlp("./P1", "./P1", (char*) NULL);
  } else {
    waitpid(child_P1, &status, 0);
    int child_P2 = fork();
    if (child_P2==0) {
      printf("Child 2");
      execlp("./P2", "./P2", (char*) NULL);
    } else {
      waitpid(child_P2, &status, 0);
    }
  }
  return 0;
}
