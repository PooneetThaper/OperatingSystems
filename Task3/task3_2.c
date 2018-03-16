#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  char *const child_args[] = {"ls", "-lat", "/usr/bin", NULL};
  int child = fork();
  int status;
  if (child==0) {
    int pid = execvp("ls", child_args);
    //int pid = execvp("ls", argv);
  } else {
    printf("Child pid: %d\n", child);
    waitpid(child, &status, 0);
  }
  return 0;
}
