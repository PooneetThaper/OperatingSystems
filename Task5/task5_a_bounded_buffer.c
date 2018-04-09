#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Bounded buffer (queue) */
int consumer_index, producer_index;
int buffer_size;
int buffer[20];

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

  /* Initialize buffer */
  consumer_index = 0;
  producer_index = 0;
  buffer_size = 20;
  for(int i=0; i<buffer_size; i++){
    buffer[i] = -1;
  }

  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tid,&attr,runner,argv[1]);

  printf("Starting productions!\n");
  for(int i=0; i<num_productions; i++){
    while((producer_index+1)%buffer_size == consumer_index){
      printf("Producer waiting for space! (consumer at %d, producer at %d)\n", consumer_index, producer_index);
    }
    buffer[i%buffer_size] = i+1;
    producer_index = (producer_index+1)%buffer_size;

    printf("Produced item %d: %d (consumer at %d, producer at %d)\n", i+1, i+1, consumer_index, producer_index);
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
    while(consumer_index == producer_index){
      printf("Consumer waiting for productions!\n");
    }
    int consumed = buffer[consumer_index];
    num_consumed++;
    consumer_index = (consumer_index+1)%buffer_size;

    printf("Consumed item %d: %d (consumer at %d, producer at %d)\n", num_consumed, consumed, consumer_index, producer_index);
  }

  printf("Consumer done consuming\n");
  pthread_exit(0);
}
