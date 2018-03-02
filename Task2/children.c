#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  int child_a = fork(); // Fork first child
  int status_a; // Declare an int for the waitpid for first child

  if(child_a == 0) { // Code for first forked child
    printf("I am child one, my pid is: %d\n", getpid());
    return 0;

  } else {
    int child_b = fork(); // Fork second child
    int status_b; // Declare an int for waitpid for second child

    if(child_b == 0) { // Code for second child
      printf("I am child two, my pid is: %d\n", getpid());
      return 0;
      
    } else {
      waitpid(child_b, &status_b, 0); // Wait for second child after forking
    }
    waitpid(child_a, &status_a, 0); // Wait for first child after forking

    // Waiting for first child is done after forking second child to not block
    // the parent before forking the second fork
  }
  return 0;
}
