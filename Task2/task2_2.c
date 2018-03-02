#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  //parent P
  printf("P pid: %d\n", getpid());
  int a=10, b=25, fq=0, fr=0;

  fq=fork(); // fork a child - call it Process Q
  if(fq==0) { // Child successfully forked
    // Fork Q of process P
    // current values: a = 10, b = 25
    printf("Q pid: %d\n", getpid());
    a=a+b;
    printf("a: %d, b: %d, pid: %d\n", a, b, getpid());
    // Output: a: 35, b: 25, pid: {Q pid}

    fr=fork(); // fork another child - call it Process R
    if(fr!=0) {
      // Process Q continues after fork of child R
      // current values: a = 35, b = 25
      b=b+20;
      printf("a: %d, b: %d, pid: %d\n", a, b, getpid());
      // Output: a: 35, b: 45, pid: {Q pid}

    } else {
      // Fork R of process Q
      // current values: a = 35, b = 25
      printf("R pid: %d\n", getpid());
      a=(a*b)+30;
      printf("a: %d, b: %d, pid: %d\n", a, b, getpid());
      // Output: a: 905, b: 25, pid: {R pid}
    }

  } else {
    // Process P continues after fork of child Q
    // current values: a = 10, b = 25
    b=a+b-5;
    printf("a: %d, b: %d, pid: %d\n", a, b, getpid());
    // Output: a: 10, b: 30, pid: {P pid}
  }
}
