#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

sem_t mutex[5];

void* phil(void* f)
{
    sleep(1);//thinking
    int i=(int)f;
    sem_wait(&mutex[i]);
    printf("philosopher %d received f%d\n",i,i);
    sem_wait(&mutex[(i+1)%5]);
    printf("philosopher %d received f%d  \n",i,(i+1)%5);
    printf("philosopher %d received two f%d f%d \n",i,i,(i+1)%5);
    sleep(1);//eating
    sem_post(&mutex[i]);
    sem_post(&mutex[(i+1)%5]);

}
void* phil1(void* f)
{
    sleep(1);//thinking
    int i=(int)f;
    sem_wait(&mutex[(i+1)%5]);
    printf("philosopher %d received f%d  \n",i,(i+1)%5);
    sem_wait(&mutex[i]);
    printf("philosopher %d received f%d  \n",i,i);
    
    printf("philosopher %d received two f%d f%d \n",i,i,(i+1)%5);
    sleep(1);//eating
    sem_post(&mutex[i]);
    sem_post(&mutex[(i+1)%5]);

}
int main(int argc, char const *argv[])
{
    /* code */
    pthread_t philosophers[5];
    int i=0;
    for(int i=0;i<5;i++)
    {
        sem_init(&mutex[i],0,1);
    }
    for(i=0;i<4;i++)
    {
        pthread_create(&philosophers[i],NULL,phil,(void*)i);
    }
    pthread_create(&philosophers[i],NULL,phil1,(void*)i);
    for(i=0;i<5;i++)
    {
        pthread_join(philosophers[i],NULL);   
        
    }
    for(int i=0;i<5;i++)
    {
        sem_destroy(&mutex[i]);
    }

    return 0;
}
