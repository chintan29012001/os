#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h> 
#include <semaphore.h> 
#include<sys/wait.h> 

sem_t text_block;
sem_t num_block;
sem_t parent_lock1;
sem_t parent_lock2;
sem_t child_lock1;
sem_t child_lock2;
int getSharedMemory(int id,int seg)
{
	key_t shared_key = ftok(".", id);
	int shared_id;
	if((shared_id = shmget(shared_key, seg, IPC_CREAT | 0666)) == -1){
		perror("Cannot retrive shared memory");
		exit(EXIT_FAILURE);
	}

	return shared_id;
}

int main(int argc, char const *argv[])
{
    
    int shared_id_text;
    int shared_id_num;
    int shared_id_address;
    shared_id_text = getSharedMemory(1,20);
    shared_id_num = getSharedMemory(2,8);
    shared_id_address=getSharedMemory(10,4);
    // mutex=sem_open(SEMAPHORE1_NAME, O_CREAT | O_EXCL, 0666, 0);
    
    sem_init(&text_block, 1, 1); 
    sem_init(&num_block, 1, 1); 
    sem_init(&parent_lock1,1,0);
    sem_init(&parent_lock2,1,0);
    sem_init(&child_lock1,1,0);
    sem_init(&child_lock2,1,0);
    
    
    
    int c=fork();
    if(c>0)
    {
        int i=10;
        // sem_post(&parent_lock);    
        char x[]="p text here";
        sem_wait(&text_block);
        char* str=shmat(shared_id_text, NULL, 0);
        memcpy(str,x,strlen(x)+1);
        shmdt(str);
        sem_post(&text_block);
        sem_post(&parent_lock1);
        i++;
        long* num=shmat(shared_id_num, NULL, 0);
        *num=i;
        shmdt(num);
        sem_post(&num_block);
        sem_post(&parent_lock2);
        // sem_wait(&address_block);
        sleep(1);
        // sem_wait(&parent_lock1);
        // sem_wait(&parent_lock1);
        sem_trywait(&child_lock1);
        sem_wait(&text_block);
        str=shmat(shared_id_text, NULL, 0);
        printf("%s \n",str);
        shmdt(str);
        sem_post(&text_block);
        sem_trywait(&child_lock2);
        sem_wait(&num_block);
        num=shmat(shared_id_num, NULL, 0);
        printf("%ld \n",*num);
        shmdt(num);
        sem_post(&num_block); 
        
        wait(NULL);
        if(shmctl(shared_id_address, IPC_RMID, NULL) == -1){
		perror("Cannot remove shared memory");
		exit(EXIT_FAILURE);
	    }
        if(shmctl(shared_id_num, IPC_RMID, NULL) == -1)
        {
            perror("Cannot remove shared memory");
            exit(EXIT_FAILURE);
        }
        
        if(shmctl(shared_id_text, IPC_RMID, NULL) == -1){
                perror("Cannot remove shared memory");
                exit(EXIT_FAILURE);
            }
        // sem_destroy(&address_block);
        sem_destroy(&text_block);
        sem_destroy(&num_block);     
         
        //parent ptocess
       
        


    }
    else
    {
        //reading
        int i=20;
        // sem_post(&parent_lock);    
        char y[]="c text here";
        sem_trywait(&parent_lock1);
        sem_wait(&text_block);
        char* str=shmat(shared_id_text, NULL, 0);
        printf("%s \n",str);
        memcpy(str,y,strlen(y)+1);
        shmdt(str);
        sem_post(&text_block);
        sem_post(&child_lock1);
        sem_trywait(&parent_lock2);
        sem_wait(&num_block);
        long* num=shmat(shared_id_num, NULL, 0);
        printf("%ld \n",*num);
        *num=i;
        shmdt(num);
        sem_post(&num_block);
        sem_post(&child_lock2); 
        // sleep(1);       
        
        

        
        
    }



    return 0;
}
