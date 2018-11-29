/******************************************************************
 * The Main program with the two functions. A simple
 * example of creating and using a thread is provided.
 ******************************************************************/

#include "helper.h"

void *producer (void *id);
void *consumer (void *id);
const int NO_OF_SEMAPHORES = 3;

key_t sem_key = SEM_KEY;
int sem_id;
 
vector<Job> circle_queue; // shared queue
int queue_pos = 0; //variable to keep track of queue position

int main (int argc, char **argv)
{
  if(argc != 5){
    cout << "Incorrect number of input parameters!" << endl;
    return 0;
  }
  
  int parameter = 5;
  int queue_size = atoi(argv[1]);
  int no_of_jobs = atoi(argv[2]);
  int no_of_producers = atoi(argv[3]);
  int no_of_consumers = atoi(argv[4]);
  pthread_t producerid[no_of_producers];
  pthread_t consumerid[no_of_consumers];

  circle_queue.resize(queue_size);
  
  vector<int>* vec_array[no_of_producers];
  
  //**Create threads for all producers
  for(int i=0; i< no_of_producers; ++i){
    vec_array[i] = new vector<int>(no_of_jobs,0);
    fill_array_random(*vec_array[i]);
    pthread_create(&producerid[i], NULL, producer, (void *)vec_array[i]);
  }

  //**Create threads for all consumers
  for(int i=0; i< no_of_consumers; ++i){
    pthread_create(&consumerid[i], NULL, consumer, NULL);
  }

  sem_id = sem_create(sem_key, NO_OF_SEMAPHORES);

  if(sem_id < 0) return 0;
  
  if(sem_init(sem_id, SEM_MUTEX, 1)) return 0;
  if(sem_init(sem_id, SEM_FULL, queue_size)) return 0;
  if(sem_init(sem_id, SEM_EMPTY, 0)) return 0;

  
  for(int i=0; i<no_of_producers; ++i){
    pthread_join (producerid[i], NULL);
    delete vec_array[i]; //Clean up vectors for durations
  }

  sem_close(sem_id);
  return 0;
}

void *producer (void *parameter) 
{
  // TODO
  vector<int> *param = (vector<int>*) parameter;
  vector<int>::iterator it = param->begin();
  while(it != param->end()){
    sem_wait(sem_id, SEM_FULL);
    sem_wait(sem_id, SEM_MUTEX);
    circle_queue[queue_pos] = Job(queue_pos, *it);
    sem_signal(sem_id, SEM_MUTEX);
    sem_signal(sem_id, SEM_EMPTY);
    cout << "Parameter = " << circle_queue[queue_pos].duration << endl;
    it++;
    //**return queue position to start of queue once out of range
    if(++queue_pos > int(circle_queue.size()-1)) queue_pos%=circle_queue.size();
  }
  pthread_exit(0);
}

void *consumer (void *id) 
{
    // TODO 

  pthread_exit (0);

}
