#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define NUM_PHILOSOPHERS 5
#define NUM_CHOPSTICKS 5

void dine(int n);
pthread_t
philosopher[NUM_PHILOSOPHERS];
pthread_mutex_t
chopstick[NUM_CHOPSTICKS];


int main()
{

    int i,status_message;
    void*msg;
    for(i=1;i<=NUM_CHOPSTICKS; i++)
    {
        status_message=pthread_mutex_init(&chopstick[i],NULL);
     if(status_message==-1)
     {
        printf("\n mutex initiliation failed");
        exit(1);

     }
    }
   
for(i=1;i<=NUM_PHILOSOPHERS;i++)

{
    status_message=pthread_create(&philosopher[i],NULL,(void*)dine,(int*)i);
    if(status_message!=0)
    {
        printf("\n  Therad creation error\n");
        exit(1);

    }
}
for(i=1;i<=NUM_PHILOSOPHERS;i++)
{
    status_message=pthread_join(philosopher[i],&msg);
    if(status_message!=0)
    {
        printf("\n Thread join failed\n");
        exit(1);
    }

    }
    for(i=1;i<=NUM_PHILOSOPHERS;i++)
    {
        status_message=pthread_mutex_destroy(&chopstick[i]);
        if(status_message!=0)
        {
            printf("\n Mutex Destroyed\n");
            exit(1);
        }
    }
    return 0;
}
void dine(int n)
{
    printf("\nPhilosopher%d is thinking",n);
    pthread_mutex_lock(&chopstick[n]);
    pthread_mutex_lock(&chopstick[(n+1)%NUM_CHOPSTICKS]);
    printf("\nphilosopher%d is eating",n);
    sleep(3);

     pthread_mutex_unlock(&chopstick[n]);
     pthread_mutex_unlock(&chopstick[(n+1)%NUM_CHOPSTICKS]);
      printf("\nphilosopher%d is finished  eating",n);
}
/* OUTPUT


Philosopher5 is thinking
philosopher5 is eating
Philosopher3 is thinking
philosopher3 is eating
Philosopher1 is thinking
Philosopher4 is thinking
Philosopher2 is thinking
philosopher5 is finished  eating
philosopher3 is finished  eating
philosopher4 is eating
philosopher2 is eating
philosopher4 is finished  eating
philosopher2 is finished  eating
philosopher1 is eating
philosopher1 is finished  eating[?2004h
*/





