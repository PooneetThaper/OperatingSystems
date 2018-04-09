#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Queue */
int *buffer;
int num_elements;
int capacity;
int current_start;
void enqueue(int message);
int dequeue();

void *runner(void *param);


int main(int argc, char *argv[]){
  /* Arguements:
     argv[1]: number of items to produce
  */
  if (argc != 2) {
  	fprintf(stderr,"usage: a.out <number of productions>\n");
  	/*exit(1);*/
  	return -1;
  }
  int num_productions = atoi(argv[1]);

  /* Initialize queue */
  buffer = malloc(10 * sizeof(int));
  num_elements = 0;
  capacity = 10;
  current_start = 0;

  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tid,&attr,runner,argv[1]);

  printf("Starting productions!\n");
  for(int i=0; i<num_productions; i++){
    while(num_elements == capacity){
      printf("Producer is waiting for space!\n");
    }
    enqueue(i+1);
    printf("Produced item %d: %d\n", i+1, i+1);
  }

  printf("Producer finished producing!\n");

  pthread_join(tid,NULL);

  return 0;
}

void *runner(void *param){
  int num_productions = atoi(param);
  int num_consumed = 0;
  printf("Consumer awaiting %d productions!\n", num_productions);

  while(num_consumed < num_productions){
    while((num_elements) ? 0 : 1){
      printf("Consumer waiting for productions!\n");
    }
    int consumed = dequeue();
    num_consumed++;

    printf("Consumed item %d: %d\n", num_consumed, consumed);
  }

  printf("Consumer done consuming\n");
  pthread_exit(0);
}

void enqueue(int message){
  /*
  if (num_elements == capacity){
    int *new_buffer = malloc(capacity * 2 * sizeof(int));
    for(int i=0; i<capacity; i++){
      new_buffer[i] = buffer[(i+current_start)%capacity];
    }
    free(buffer);
    buffer = new_buffer;
    current_start = 0;
    capacity *= 2;
  }
  */

  buffer[(current_start + num_elements++)%capacity] = message;
}

int dequeue(){
  int retval = buffer[current_start];
  current_start = (current_start+1)%capacity;
  num_elements--;
  return retval;
}
