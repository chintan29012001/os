
#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>




struct my_semaphore
{
   int entry;
   pthread_mutex_t* lock;
   pthread_cond_t* cond;
};

struct my_semaphore* forks;
struct my_semaphore* sauce;
int total_philosophers;

//this function initializes the semaphores of forks and sauce bowl
void initialize(int n)
{
   
   total_philosophers=n;
   forks=(struct my_semaphore*)malloc(sizeof(struct my_semaphore)*n);
   for(int i=0;i<n;i++)
   {
      forks[i].entry=1;
      forks[i].lock=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
      forks[i].cond=(pthread_cond_t*)malloc(sizeof(pthread_cond_t));
      pthread_mutex_init(forks[i].lock,NULL);
      pthread_cond_init(forks[i].cond,NULL);
   }
   sauce=(struct my_semaphore*)malloc(sizeof(struct my_semaphore));
   sauce->entry=1;
   sauce->lock=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
   sauce->cond=(pthread_cond_t*)malloc(sizeof(pthread_cond_t));
   pthread_mutex_init(sauce->lock,NULL);
   pthread_cond_init(sauce->cond,NULL);  
   //printf("ini complete \n");
   
}
//this function is used to take lock of fork of the given index
void take_fork(int index)
{
      pthread_mutex_lock(forks[index].lock);
      forks[index].entry-=1;
      if(forks[index].entry<0)
      {
         pthread_mutex_unlock(forks[index].lock);
         // printf("locked and waiting %d \n",ar.entry_allowed);
         pthread_mutex_t temp;
         pthread_mutex_init(&temp,NULL);
         pthread_mutex_lock(&temp);
         pthread_cond_wait(forks[index].cond,&temp);
         pthread_mutex_unlock(&temp);
         // printf("woken up\n");
         
      }
      else
         pthread_mutex_unlock(forks[index].lock);

}
//this function is used to take lock of sauce bowl
void take_sauces()
{
      pthread_mutex_lock(sauce->lock);
      sauce->entry-=1;
      if(sauce->entry<0)
      {
         pthread_mutex_unlock(sauce->lock);
         // printf("locked and waiting %d \n",ar.entry_allowed);
         pthread_mutex_t temp;
         pthread_mutex_init(&temp,NULL);
         pthread_mutex_lock(&temp);
         pthread_cond_wait(sauce->cond,&temp);
         pthread_mutex_unlock(&temp);
         // printf("woken up\n");
         
      }
      else
         pthread_mutex_unlock(sauce->lock);

}
// implementation of blocking wait
void wait(int index)
{
   //printf("in wait %d \n",index);
   int sec=(index+1)%total_philosophers;
   if(index%2==0)
   {
      take_sauces();
      take_fork(index);
      take_fork(sec);  
      

   }
   else
   {
      take_sauces();
      take_fork(sec);
      take_fork(index);
       

   }
   
   //printf("out of wait %d \n",index);
}
//it is used to release the forks of given index 
void release_fork(int index)
{
   pthread_mutex_lock(forks[index].lock);
   forks[index].entry+=1;
   if(forks[index].entry<=0)
      pthread_cond_signal(forks[index].cond);
   pthread_mutex_unlock(forks[index].lock);
}
//it is used to release the sauce
void release_sauce()
{
   pthread_mutex_lock(sauce->lock);
   sauce->entry+=1;
   if(sauce->entry<=0)
      pthread_cond_signal(sauce->cond);
   pthread_mutex_unlock(sauce->lock);

}
//implementation of blocking signal
void signal(int index)
{
   //printf("in signal %d \n",index);
   int sec=(index+1)%total_philosophers;
   release_fork(index);
   release_fork(sec);
   release_sauce();
}

//print the val of fork semaphore of given index
void print_val_fork(int index)
{
   pthread_mutex_lock(forks[index].lock);
   printf("fork %d  val %d\n",index,forks[index].entry);
   pthread_mutex_unlock(forks[index].lock);

}
//print the val of sauce semaphore
void print_val_sauce()
{
   pthread_mutex_lock(sauce->lock);
   printf("sauce val %d\n",sauce->entry);
   pthread_mutex_unlock(sauce->lock);

}

//it is print val used to print the val of forks of the current philosopher 
void signal_printval(int index)
{
   print_val_fork(index);
   int sec=(index+1)%total_philosophers;
   print_val_fork(sec);
   print_val_sauce();
}

//it is used for creating thread
void *philosopher(int i)
{
   
      while(1)
    {
      wait(i);
      printf("Philosopher %ld eats using forks %d and %d  \n",pthread_self(),i,(i+1)%total_philosophers);//eating
      // signal_printval(i);
      sleep(1);//eating
      signal(i);
      sleep(1);//thinking
    } 
   

}
int main()
{
 
   int n=0;
   printf("enter the no of philosophers \n");
   scanf("%d",&n);   
   initialize(n);
   pthread_t* ar1=(pthread_t*)malloc(sizeof(pthread_t)*n);
   for(int i=0;i<n;i++)
   {
      pthread_create(&ar1[i],NULL,philosopher,i);
      // sleep(1);
   }
   for(int i=0;i<n;i++)
   {
      pthread_join(ar1[i],NULL);

   }
   for(int i=0;i<n;i++)
   {
      free(forks[i].lock);
      free(forks[i].cond);
      free(&forks[i]);

   }   
   free(&sauce->lock);
   free(&sauce->cond);
   free(sauce);
   free(ar1);
   free(forks);
   sleep(1);
   exit(0);
}

