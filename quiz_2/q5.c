#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>



sem_t mutex,writeblock;


// int getSharedMemory(char id);
// void removeSharedMemory(int shared_id);
int getSharedMemory(char id,int seg){
	/*
	* Generate a key
	* ftok is a hashing function that produce
	* a key by combining a file (current directory) and a byte (id)
	*/
	key_t shared_key = ftok(".", id);
	// printf("Created key %X\n", shared_key);

	// Get shared memory
	int shared_id;
	if((shared_id = shmget(shared_key, seg, IPC_CREAT | 0666)) == -1){
		perror("Cannot retrive shared memory");
		exit(EXIT_FAILURE);
	}

	return shared_id;
}

void *reader(void *arg)
{
  int f;
  int* rcount;
  f = ((int)arg);
  int rc_key=getSharedMemory(1,4);
  sem_wait(&mutex);
  rcount = shmat(rc_key, NULL, 0);
  *rcount = *rcount + 1;
  if(*rcount==1)
   sem_wait(&writeblock);
  shmdt(rcount);
  sem_post(&mutex);
  int data_key=getSharedMemory(2,8);
  long* data=shmat(data_key, NULL, 0);
  printf("Data read by the reader%d is %ld\n",f,*data);
  shmdt(data);
  // sleep(1);
  sem_wait(&mutex);
  rcount = shmat(rc_key, NULL, 0);
  *rcount = *rcount - 1;
  if(*rcount==0)
   sem_post(&writeblock);
  shmdt(rcount);
  sem_post(&mutex);
}

void *writer(void *arg)
{
  int f;
  f = ((int) arg);
  sem_wait(&writeblock);
  int data_key=getSharedMemory(2,8);
  long* data=shmat(data_key, NULL, 0);
  ++*data;
  printf("Data writen by the writer%d is %ld\n",f,*data);
  shmdt(data);
  sem_post(&writeblock);
  // sleep(1);
  
}

int main()
{
  int i,b; 
  pthread_t rtid[10],wtid[10];
  sem_init(&mutex,0,1);
  sem_init(&writeblock,0,1);
  int data_key=getSharedMemory(2,8);
  long* data=shmat(data_key, NULL, 0);
  *data=0;
  shmdt(data);
  int j=0;
  int k=0;
  i=0;
  while(k<10||j<10)
  {
    if(j<10)
    {
      pthread_create(&wtid[j],NULL,writer,(void *)j);
      j++;

    }
    if(k<10)
    {
      pthread_create(&rtid[k],NULL,reader,(void *)k);
      k++;

    }
    i++;
    
  }
  for(i=0;i<10;i++)
  {
    pthread_join(wtid[i],NULL);   
    
  }
  for(i=0;i<10;i++)
  {
    pthread_join(rtid[i],NULL);   
    
  }
  
  return 0;
}