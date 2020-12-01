
#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

struct node
{
   // pthread_t thread_id;
   int index;
   struct node* next;
};
struct queue
{
   struct node* front;
   struct node* rear;
};
void insert(struct queue* q,int i)
{
   struct node* n=(struct node*)malloc(sizeof(struct node));
   n->index=i;
   n->next=NULL;
   if(q->front==NULL)
   {
      //printf("front is null\n");
      q->rear=n;
      q->front=q->rear;  
   }
   else
   {
      q->rear->next=n;
      q->rear=q->rear->next;
   }
   //printf("Inserted node \n");
   //printf("front %d\n",q->front->index);
   
}
void delete(struct queue* q)
{
   if(q->front==NULL)
      return;
   else
   {
      q->front=q->front->next;
      if(q->front==NULL)
      {
         q->rear=NULL;
      }
   } 
}


struct my_semaphore
{
   int entry_allowed;
   int total_philosophers;
   pthread_mutex_t* forks;
   pthread_mutex_t* sauce;
   struct queue* q;
   pthread_mutex_t* vr_sem;
   pthread_mutex_t* qu_sem;
   pthread_mutex_t* thread_sleep_locks; 
   pthread_cond_t* thread_sleep_locks_cond;

}ar;


void initialize(int n)
{
   //printf("ini started \n");
   ar.total_philosophers=n;
   ar.entry_allowed=n;
   ar.vr_sem=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
   ar.qu_sem=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
   ar.forks=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*n);
   ar.thread_sleep_locks=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*n);
   ar.thread_sleep_locks_cond=(pthread_cond_t*)malloc(sizeof(pthread_cond_t)*n);
   ar.sauce=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*2);
   ar.q=(struct queue*)malloc(sizeof(struct queue));
   //printf("memory allocated \n");
   for(int i=0;i<n;i++)
   {
      pthread_mutex_init(&ar.forks[i],NULL);
   }
   pthread_mutex_init(ar.vr_sem,NULL);
   pthread_mutex_init(ar.qu_sem,NULL);
   //printf("ini complete \n");
   
}
//first n-1 philosophers pich their chopsticks and then they try to to get sauces whoever gets the first eats and the releases it
void wait(int index)
{
   //printf("in wait %d \n",index);
   pthread_mutex_lock(ar.vr_sem);
   ar.entry_allowed-=1;
   // pthread_mutex_unlock(ar.vr_sem);
   if(ar.entry_allowed<0)
   {
      pthread_mutex_unlock(ar.vr_sem);
      
      //printf("entry was not allowed \n");
      pthread_mutex_lock(ar.qu_sem);
      insert(ar.q,index);
      pthread_mutex_unlock(ar.qu_sem);
      pthread_mutex_lock(&ar.thread_sleep_locks[index]);
      //printf("locked and waiting \n");
      
      pthread_cond_wait(&ar.thread_sleep_locks_cond[index],&ar.thread_sleep_locks[index]);
      //printf("woken up\n");
      pthread_mutex_unlock(&ar.thread_sleep_locks[index]);
   }
   else
      pthread_mutex_unlock(ar.vr_sem);
   if(index%2==0)
   {
      pthread_mutex_lock(&ar.thread_sleep_locks[index]);
      pthread_mutex_lock(&ar.thread_sleep_locks[(index+1)%ar.total_philosophers]);
      pthread_mutex_lock(&ar.sauce[0]);
      pthread_mutex_lock(&ar.sauce[1]); 

   }
   else
   {
      pthread_mutex_lock(&ar.thread_sleep_locks[(index+1)%ar.total_philosophers]);
      pthread_mutex_lock(&ar.thread_sleep_locks[index]);
      pthread_mutex_lock(&ar.sauce[0]);
      pthread_mutex_lock(&ar.sauce[1]); 

   }
   
   
   //printf("out of wait %d \n",index);
}
void signal(int index)
{
   //printf("in signal %d \n",index);
   pthread_mutex_lock(ar.vr_sem);
   ar.entry_allowed+=1;
   pthread_mutex_unlock(ar.vr_sem);
   pthread_mutex_unlock(&ar.thread_sleep_locks[index]);
   pthread_mutex_unlock(&ar.thread_sleep_locks[(index+1)%ar.total_philosophers]);
   pthread_mutex_unlock(&ar.sauce[0]);
   pthread_mutex_unlock(&ar.sauce[1]); 
   pthread_mutex_lock(ar.vr_sem);
   if(ar.entry_allowed<=0)
   {
      pthread_mutex_unlock(ar.vr_sem);
      //printf("released sem  \n");
      pthread_mutex_lock(ar.qu_sem);
      struct node* n=ar.q->front;
      pthread_mutex_unlock(ar.qu_sem);
      //printf("n %ld \n",&n);
      if(n!=NULL)
      {
         // //printf("waking up %d \n",n->index);
         //printf("waking up %d \n",n->index);
         pthread_mutex_lock(&ar.thread_sleep_locks[n->index]);
         //printf("acquired the lock %d \n",n->index);
         // pthread_mutex_unlock(ar.sem);
         pthread_cond_signal(&ar.thread_sleep_locks_cond[n->index]);
         pthread_mutex_unlock(&ar.thread_sleep_locks[n->index]);
         // sleep(1);
         pthread_mutex_lock(ar.qu_sem);
         delete(ar.q);  
         pthread_mutex_unlock(ar.qu_sem);
      }
      
      free(n);
   }
   else
      pthread_mutex_unlock(ar.vr_sem);
   //printf("out of signal %d \n",index);
   

}
void *philosopher(int i)
{
   
      while(1)
    {
      wait(i);
      // pthread_mutex_lock(ar.vr_sem);
      printf("Philosopher %lld eats using forks %d and %d \n",pthread_self(),i,(i+1)%ar.total_philosophers);
      sleep(1);
      signal(i);
      sleep(1);
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
         pthread_mutex_destroy(&ar.thread_sleep_locks[i]);
         pthread_mutex_destroy(&ar.forks[i]);
         // pthread_mutex_destroy(&ar.thread_sleep_locks_cond[i]);
      }
      pthread_mutex_destroy(ar.vr_sem);
      pthread_mutex_destroy(ar.qu_sem);
      pthread_mutex_destroy(&ar.sauce[0]);
      pthread_mutex_destroy(&ar.sauce[1]);
      free(ar1);
      free(ar.q);
      sleep(1);
   exit(0);
}

