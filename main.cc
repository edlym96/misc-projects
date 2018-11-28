/******************************************************************
 * The Main program with the two functions. A simple
 * example of creating and using a thread is provided.
 ******************************************************************/

#include "helper.h"

void *producer (void *id);
void *consumer (void *id);
const int NO_OF_SEMAPHORES = 3;

int main (int argc, char **argv)
{
  if(argc != 5){
    cout << "Incorrect number of input parameters!" << endl;
    return 0;
  }

  key_t sem_key;
  int parameter = 5;
  int queue_size = atoi(argv[1]);
  int no_of_jobs = atoi(argv[2]);
  int no_of_producers = atoi(argv[3]);
  int no_of_consumers = atoi(argv[4]);
  pthread_t producerid[no_of_producers];
  pthread_t consumerid[no_of_consumers];
  int sem_id;

  Job circle_queue[queue_size];

  //**Randomise sem-key
  if((sem_key = ftok("/tmp", 'a')) == (key_t) -1){
    cout << "key failed" << endl;
    return 0;
  } 
  
  //**Create threads for all producers
  for(int i=0; i< no_of_producers; ++i){
    pthread_create(&producerid[i], NULL, producer, (void *) &parameter);
  }

  //**Create threads for all consumers
  for(int i=0; i< no_of_consumers; ++i){
    pthread_create(&consumerid[i], NULL, consumer, NULL);
  }

  //PROBLEM INITIALISING SEM ID
  sem_id = sem_create(sem_key, NO_OF_SEMAPHORES);
  if (sem_id < 0) return 0;
  
  //PROBLEM INITIALISING SEMAPHORES
  cout << sem_init(sem_id, 0, 1) << endl;
  //  if(sem_init(sem_id, 1, queue_size)) return 0;
  //if(sem_init(sem_id, 2, 0)) return 0;
 
  for(int i=0; i<no_of_producers; ++i){
    pthread_join (producerid[i], NULL);
  }
  return 0;
}

void *producer (void *parameter) 
{

  // TODO
  int *param = (int *) parameter;
  
  cout << "Parameter = " << *param << endl;

  pthread_exit(0);
}

void *consumer (void *id) 
{
    // TODO 

  pthread_exit (0);

}
