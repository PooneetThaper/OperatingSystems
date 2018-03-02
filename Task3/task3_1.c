#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  int child = fork();
  int status;
  if (child==0) {
    execl("/bin/date", "/bin/date", (char*) NULL);
  } else {
    printf("Child pid: %d", child);
    waitpid(child, &status, 0);
  }
  return 0;
}
