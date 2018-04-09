#include <stdio.h>
/* shm_* stuff, and mmap() */
#include <sys/mman.h>
#include <sys/types.h>
/* exit() etc */
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
/* for random() stuff */
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX_MSG_LENGTH      50
#define TYPES               8

struct msg_s {
    char content[MAX_MSG_LENGTH];
    int type;
};

void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[]){
  void *shm_name = "/posix_shared_mem";
  int shmfd = shm_open(shm_name, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);
  printf("Parent created shared memory %s\n", shm_name);

  pthread_t producertid;
  pthread_t consumertid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  pthread_create(&producertid,&attr,producer,shm_name);
  pthread_create(&consumertid,&attr,consumer,shm_name);
  pthread_join(producertid,NULL);
  pthread_join(consumertid,NULL);
}

void *producer(void *param){
  printf("Producer writing to %s\n", param);
  int shared_seg_size = (1 * sizeof(struct msg_s));
  struct msg_s *shared_msg;

  int shmfd = shm_open(param, O_RDWR, S_IRWXU | S_IRWXG);
  if (shmfd < 0) {
      perror("In shm_open()");
      exit(1);
  }
  fprintf(stderr, "Created shared memory object %s\n", param);
  ftruncate(shmfd, shared_seg_size);

  shared_msg = (struct msg_s *)mmap(NULL, shared_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
  if (shared_msg == NULL) {
      perror("In mmap()");
      exit(1);
  }

  srandom(time(NULL));
  shared_msg->type = random() % TYPES;
  snprintf(shared_msg->content, MAX_MSG_LENGTH, "My message, type %d, num %ld", shared_msg->type, random());
  printf("Produce wrote message to %s\n", param);

  pthread_exit(0);
}

void *consumer(void *param){
  printf("Consumer reading from %s\n",param);
  int shmfd = shm_open(param, O_RDWR, S_IRWXU | S_IRWXG);
  if (shmfd < 0) {
      perror("In shm_open()");
      exit(1);
  }
  int shared_seg_size = (1 * sizeof(struct msg_s));
  struct msg_s *shared_msg;

  shared_msg = (struct msg_s *)mmap(NULL, shared_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
  if (shared_msg == NULL) {
      perror("In mmap()");
      exit(1);
  }
  printf("Consumer read: %s\n", shared_msg->content);

  pthread_exit(0);
}
