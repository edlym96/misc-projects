/******************************************************************
 * The Main program with the two functions. A simple
 * example of creating and using a thread is provided.
 ******************************************************************/

#include "helper.h"

void *producer (void *id);
void *consumer (void *id);
const int NO_OF_SEMAPHORES = 3;

int sem_id;
int flag = 0;

int main (int argc, char **argv)
{
  srand(time(0));
  if(argc != 5){
    cout << "Incorrect number of input parameters!" << endl;
    return 0;
  }

  //** Initialise variables 
  key_t sem_key = SEM_KEY;
  int queue_size = check_arg(argv[1]);
  int no_of_jobs = check_arg(argv[2]);
  int no_of_producers = check_arg(argv[3]);
  int no_of_consumers = check_arg(argv[4]);

  //** Catch any errors wit arguments
  if(queue_size <0 || no_of_jobs < 0 || no_of_producers < 0 || no_of_consumers < 0){
    cerr << "invalid input arguments" << endl;
    return 0;
  }

  //** create sem_id
  sem_id = sem_create(sem_key, NO_OF_SEMAPHORES);
  if(sem_id < 0) exit(EXIT_FAILURE);
  
  signal(SIGHUP, signal_handler);
  signal(SIGABRT, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGTSTP, signal_handler);
  signal(SIGTERM, signal_handler);
  signal(SIGKILL, signal_handler);
  signal(SIGSEGV, signal_handler);
  atexit(exit_function);

  //** Initialise semaphores
  cout << sem_id << endl;
  if(sem_init(sem_id, SEM_MUTEX, 1)) exit(EXIT_FAILURE);
  if(sem_init(sem_id, SEM_FULL, queue_size)) exit(EXIT_FAILURE);
  if(sem_init(sem_id, SEM_EMPTY, 0)) exit(EXIT_FAILURE);

  //** Create array for threads
  pthread_t producerid[no_of_producers];
  pthread_t consumerid[no_of_consumers];

  //**Initialise shared data structures for producers/consumers
  Circle_Queue shared_queue = Circle_Queue(queue_size);

  //**Create arguments for all producers
  Producer_Arg producer_arg_array[no_of_producers];
  for(int i=0; i< no_of_producers; ++i){
    producer_arg_array[i] = Producer_Arg(shared_queue, i+1, no_of_jobs);
  }

  //**Create arguments for all consumers
  Consumer_Arg consumer_arg_array[no_of_consumers];
  for(int i=0; i< no_of_consumers; ++i){
    consumer_arg_array[i] = Consumer_Arg(shared_queue, i+1);
  }

  //** Create threads for all producers
  for(int i=0; i< no_of_producers; ++i){
    pthread_create(&producerid[i], NULL, producer, (void *)&producer_arg_array[i]);
  }

  //** Create threads for all consumers
  for(int i=0; i< no_of_consumers; ++i){
    pthread_create(&consumerid[i], NULL, consumer, (void *)&consumer_arg_array[i]);
  }

  //** Join producers
  for(int i=0; i<no_of_producers; ++i){
    if(pthread_join (producerid[i], NULL)){
      cout << "error joining thread" << endl;
      exit(EXIT_FAILURE);
    }
  }
  
  //** Join consumers
  for(int i=0; i<no_of_consumers; ++i){
    if(pthread_join (consumerid[i], NULL)){
      cout << "error joining thread" << endl;
      exit(EXIT_FAILURE);
    }
  }

  //** Close semaphore
  sem_close(sem_id);
  return 0;
}

void *producer (void *parameter) 
{

  Producer_Arg* param = (Producer_Arg *)parameter;
  vector<Job*>& queue_ref = (param->circle_queue)->queue;
  int& queue_end_ref = (param->circle_queue)->queue_end;
  while(param->jobs_remaining>0){
    if(sem_down(sem_id, SEM_FULL, TIMEOUT_DURATION) < 0){
      cout << "Queue full, no more jobs" << endl;
      pthread_exit(0);
    }
    sem_wait(sem_id, SEM_MUTEX);
    //**BEGIN CRITICAL REGION
    queue_ref[queue_end_ref] = new Job(queue_end_ref+1, (rand()%10)+1);
    cerr << "Producer(" << param->id << "): " << "Job ID " << queue_ref[queue_end_ref]->index << " Duration " << queue_ref[queue_end_ref]->duration << endl;
    
    //**return queue position to start of queue once out of range
    if(++queue_end_ref > int(queue_ref.capacity()-1)) queue_end_ref=0;
    
    //**END CRITICAL REGION
    sem_signal(sem_id, SEM_MUTEX);
    sem_signal(sem_id, SEM_EMPTY);
    (param->jobs_remaining)--;
    if(param->jobs_remaining == 0){
      cout << "Producer(" << param->id << "): No more jobs to generate" << endl;
    }else{
      sleep((rand()%5));
    }
  }
  pthread_exit(0);
}

void *consumer (void *id) 
{
  Consumer_Arg* param = (Consumer_Arg *)id;
  vector<Job*>& queue_ref = (param->circle_queue)->queue;
  int& queue_start_ref = (param->circle_queue)->queue_start;
  Job current_job;

  while(1){
    if(sem_down(sem_id, SEM_EMPTY, TIMEOUT_DURATION) < 0){
      cout << "Consumer(" << param->id << "): " << "No more jobs left." << endl;
      pthread_exit(0);
    }
    sem_wait(sem_id, SEM_MUTEX);
    //**BEGIN CRITICAL REGION
    current_job = *(queue_ref[queue_start_ref]);
    queue_ref[queue_start_ref]->~Job();
    queue_ref[queue_start_ref] = NULL;
    cout << "Consumer(" << param->id << "): " << "Job ID " << current_job.index << " executing sleep duration " << current_job.duration << endl;
    if(++queue_start_ref > int(queue_ref.capacity()-1)) queue_start_ref = 0;
    //**END CRITICAL REGION
    sem_signal(sem_id, SEM_MUTEX);
    sem_signal(sem_id, SEM_FULL);
    sleep(current_job.duration);
    cout << "Consumer(" << param->id << "): " << "Job ID " << current_job.index << " completed" << endl;
  }
  cout << "outside the while loop" << endl;
  pthread_exit (0);
}
