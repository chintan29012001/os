
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
   //printf("ini started \n");
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
int take_fork(int index)
{
      if(pthread_mutex_trylock(forks[index].lock)!=0)
         return 1;
      forks[index].entry-=1;
      if(forks[index].entry<0)
      {
         forks[index].entry+=1;
         pthread_mutex_unlock(forks[index].lock);
         // printf("locked and waiting %d \n",ar.entry_allowed);
         return 1;
         // printf("woken up\n");
         
      }
      else
         pthread_mutex_unlock(forks[index].lock);
      return 0;

}
//this function is used to take lock of sauce bowl
int take_sauces()
{
      if(pthread_mutex_trylock(sauce->lock)!=0)
         return 1;
      sauce->entry-=1;
      if(sauce->entry<0)
      {
         sauce->entry+=1;
         pthread_mutex_unlock(sauce->lock);
         // printf("locked and waiting %d \n",ar.entry_allowed);
         return 1;
         // printf("woken up\n");
         
      }
      else
         pthread_mutex_unlock(sauce->lock);
      return 0;
}

// implementation of non blocking wait
int wait(int index)
{
   //printf("in wait %d \n",index);
   int sec=(index+1)%total_philosophers;
   if(take_sauces()!=0)
         return 1;
   if(index%2==0)
   {
      
      if(take_fork(index)!=0)
         return 1;
      if(take_fork(sec)!=0)
      {
         release_fork(index);
         return 2;  

      }

   }
   else
   {
      if(take_fork(sec)!=0)
         return 1;
      if(take_fork(index)!=0)
      {
         release_fork(sec);
         return 3;
      }
       

   }
   return 0;
   
   //printf("out of wait %d \n",index);
}
//it is used to release the forks of given index 
int release_fork(int index)
{
   pthread_mutex_lock(forks[index].lock);
   forks[index].entry+=1;
   pthread_mutex_unlock(forks[index].lock);
   
}
//it is used to release the sauce
void release_sauce()
{
   pthread_mutex_lock(sauce->lock);
   sauce->entry+=1;
   pthread_mutex_unlock(sauce->lock);

}

//it is used to non block release the forks of given index 
int release_fork_non_block(int index)
{
   if(pthread_mutex_trylock(forks[index].lock)!=0)
      return 1;
   forks[index].entry+=1;
   pthread_mutex_unlock(forks[index].lock);

}

//it is used to non block release the sauce
int release_sauce_non_block()
{
   if(pthread_mutex_lock(sauce->lock)!=0)
      return 1;
   sauce->entry+=1;
   pthread_mutex_unlock(sauce->lock);

}

//implementation of non blocking signal
int signal(int index)
{
   //printf("in signal %d \n",index);
   int sec=(index+1)%total_philosophers;
   if(release_fork_non_block(index)!=0)
      return 1;
   if(release_fork_non_block(sec)!=0)
      return 2;
   if(release_sauce_non_block()!=0)
      return 3;
   return 0;
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

//non blocking print the val of fork semaphore of given index
void print_val_fork_non_blocking(int index)
{
   if(pthread_mutex_trylock(forks[index].lock)!=0)
      return;
   printf("fork %d  val %d\n",index,forks[index].entry);
   pthread_mutex_unlock(forks[index].lock);

}
//non blocking print the val of sauce semaphore
void print_val_sauce_non_blocking()
{
   if(pthread_mutex_trylock(sauce->lock)!=0)
      return;
   printf("sauce val %d\n",sauce->entry);
   pthread_mutex_unlock(sauce->lock);

}

//it is non blocking print val used to print the val of forks of the current philosopher
int signal_printval_non_blocking(int index)
{
   print_val_fork_non_blocking(index);
   int sec=(index+1)%total_philosophers;
   print_val_fork_non_blocking(sec);
   print_val_sauce_non_blocking();
}

//it is used for creating thread
void *philosopher(int i)
{
   
      while(1)
    {
      
      // printf("start\n");
      int x=wait(i);
      switch (x)
      {
      case 2:release_fork(i);
         break;
      case 3:release_fork((i+1)%total_philosophers);
         break;
      }
      if(x!=0)
         continue;
      
      printf("Philosopher %ld eats using forks %d and %d  \n",pthread_self(),i,(i+1)%total_philosophers);
      // signal_printval(i);
      // signal_printval_non_blocking(i);
      
      
      sleep(1);
      int y=signal(i);
      
      switch(y)
      {
         case 3:release_sauce();
         case 2:release_fork((i+1)%total_philosophers);
         case 1:release_fork(i);break;
      }
      sleep(1);
      // printf("exit\n");
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

