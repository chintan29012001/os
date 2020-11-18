#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h> 
#include <semaphore.h> 
#include<sys/wait.h> 

sem_t mutex;
sem_t mutex1;
sem_t mutex2;

int main(int argc, char const *argv[])
{
    // key_t shared_key = ftok(".", 0);
    key_t shared_key1 = ftok(".", 1);
    key_t shared_key2 = ftok(".", 2);
    // int shared_id;
    int shared_id1;
    int shared_id2;
    // mutex=sem_open(SEMAPHORE1_NAME, O_CREAT | O_EXCL, 0666, 0);
    sem_init(&mutex, 1, 1);
    sem_init(&mutex1, 1, 1); 
    // shared_id = shmget(shared_key, 512, IPC_CREAT | 0666);
    shared_id1 = shmget(shared_key1, 512, IPC_CREAT | 0666);
    shared_id2 = shmget(shared_key1, 1, IPC_CREAT | 0666);
    
    int c=fork();
    if(c>0)
    {

        //parent ptocess
        char* shared_memory_text;
        int* written_to_shared;
        // int* shared_memory_num;
        FILE *fp;
        fp=fopen("para1.txt","r");
        if(fp==NULL)
            return 1;
        char buf[512];
        // sem_wait(&mutex);
        // written_to_shared=shmat(shared_id2, NULL, 0);
        // *written_to_shared=0;
        // shmdt(written_to_shared);
        // sem_post(&mutex);
        sem_wait(&mutex1);
        shared_memory_text = shmat(shared_id1, NULL, 0);        
        if(fgets(buf,512,fp))
        {
            printf("%s\n",buf);
            memcpy(shared_memory_text,buf,strlen(buf)+1); 
        }
        shmdt(shared_memory_text);
        sem_post(&mutex1);
        sem_wait(&mutex);
        written_to_shared=shmat(shared_id2, NULL, 0);
        *written_to_shared=1;
        printf("%d",*written_to_shared);
        shmdt(written_to_shared);
        sem_post(&mutex); 
                   
        wait(NULL);
        


    }
    else
    {
        //child process
        char* shared_memory_text;
        int* written_to_shared;
        char buf[512];
        while (1)
        {
            sem_wait(&mutex);
            written_to_shared=shmat(shared_id2, NULL, 0);
            if(*written_to_shared==1)
            {
                break;
            }
            shmdt(written_to_shared);
            sem_post(&mutex);
                
                
            
        }
        
        sem_wait(&mutex1);
        shared_memory_text = shmat(shared_id1, NULL, 0);        
        printf("%s\n",shared_memory_text);
        shmdt(shared_memory_text);
        sem_post(&mutex1);
                    
        
        
    }



    return 0;
}
