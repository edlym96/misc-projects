/******************************************************************
 * The Main program with the two functions. A simple
 * example of creating and using a thread is provided.
 ******************************************************************/

#include "helper.h"

void *producer (void *id);
void *consumer (void *id);
const int NO_OF_SEMAPHORES = 3;

int sem_id;
int no_of_jobs; 
vector<Job> circle_queue; // shared queue
int queue_end = 0; //variable to keep track of queue position
int queue_start = 0;

int main (int argc, char **argv)
{
  if(argc != 5){
    cout << "Incorrect number of input parameters!" << endl;
    return 0;
  }

  key_t sem_key = SEM_KEY;
  //  int parameter = 5;
  int queue_size = atoi(argv[1]);
  no_of_jobs = atoi(argv[2]);
  int no_of_producers = atoi(argv[3]);
  int no_of_consumers = atoi(argv[4]);
  pthread_t producerid[no_of_producers];
  pthread_t consumerid[no_of_consumers];
  circle_queue.resize(queue_size);
  
  //**Create threads for all producers
  for(int i=0; i< no_of_producers; ++i){
    pthread_create(&producerid[i], NULL, producer, (void *)&i);
  }

  //**Create threads for all consumers
  for(int i=0; i< no_of_consumers; ++i){
    pthread_create(&consumerid[i], NULL, consumer, (void *)&i);
  }

  sem_id = sem_create(sem_key, NO_OF_SEMAPHORES);
  cout << sem_id << endl;
  if(sem_id < 0) exit(1);
  
  if(sem_init(sem_id, SEM_MUTEX, 1)) exit(1);
  if(sem_init(sem_id, SEM_FULL, queue_size)) exit(1);
  if(sem_init(sem_id, SEM_EMPTY, 0)) exit(1);

  
  for(int i=0; i<no_of_producers; ++i){
    if(pthread_join (producerid[i], NULL)){
      cout << "error joining thread" << endl;
      exit(1);
    }
  }

  for(int i=0; i<no_of_consumers; ++i){
    if(pthread_join (consumerid[i], NULL)){
      cout << "error joining thread" << endl;
      exit(1);
    }
  }
  
  sem_close(sem_id);
  return 0;
}

void *producer (void *parameter) 
{
  // TODO
  int* param = (int *)parameter;
  int jobs_remaining = no_of_jobs;
  srand((int)time(0));
  while(jobs_remaining>0){
    Job new_job = Job(queue_end, (rand()%10)+1);
    sem_wait(sem_id, SEM_FULL);
    sem_wait(sem_id, SEM_MUTEX);
    circle_queue[queue_end] = new_job;
    sem_signal(sem_id, SEM_MUTEX);
    sem_signal(sem_id, SEM_EMPTY);
    cout << "Producer(" << *param << "): " << circle_queue[queue_end].duration << endl;
    jobs_remaining--;
    //**return queue position to start of queue once out of range
    if(++queue_end > int(circle_queue.size()-1)) queue_end=0;
  }
  pthread_exit(0);
}

void *consumer (void *id) 
{
    // TODO
  int* consumer_id = (int *)id;
  //Fix while loop
  while(1){
    Job current_job;
    sem_wait(sem_id, SEM_EMPTY);
    sem_wait(sem_id, SEM_MUTEX);
    current_job = circle_queue[queue_start];
    circle_queue.erase(circle_queue.begin() + queue_start);
    sem_signal(sem_id, SEM_MUTEX);
    sem_signal(sem_id, SEM_FULL);
    if(++queue_start > int(circle_queue.size()-1)) queue_start = 0;
    cout << "Consumer(" << *consumer_id << "):" << current_job.duration << endl;
    sleep(curret_job.duration);
  }
  pthread_exit (0);

}
