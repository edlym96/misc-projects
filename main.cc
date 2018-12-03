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
  //**Delete existing semaphore set if it exists
  /*
  string s("ipcrm -S ");
  s+=to_string(SEM_KEY);
  const char* cmd = s.c_str();
  system(cmd);
  */
  
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

  //** Catch any errors with arguments
  if(queue_size <=0 || no_of_jobs < 0 || no_of_producers < 0 || no_of_consumers < 0){
    cerr << "Invalid input arguments" << endl;
    return 0;
  }

  //** create sem_id
  sem_id = sem_create(sem_key, NO_OF_SEMAPHORES);
  if(sem_id < 0) exit(EXIT_FAILURE);
  
  signal(SIGHUP, signal_handler);
  signal(SIGABRT, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGILL, signal_handler);
  signal(SIGTERM, signal_handler);
  signal(SIGSEGV, signal_handler);
  atexit(exit_function);

  //** Initialise semaphores
  if(sem_init(sem_id, SEM_MUTEX, 1)) {
    cout << "Failure initialising MUTEX semaphore" << endl;
    exit(EXIT_FAILURE);
  }
  if(sem_init(sem_id, SEM_FULL, queue_size)){
    cout << "Failure initialising FULL semaphore" << endl;
    exit(EXIT_FAILURE);
  }
  if(sem_init(sem_id, SEM_EMPTY, 0)){
    cout << "Failure initialising EMPTY semaphore" << endl;
    exit(EXIT_FAILURE);
  }

  //** Create array for threads
  pthread_t producerid[no_of_producers];
  pthread_t consumerid[no_of_consumers];

  //**Initialise shared data structures for producers/consumers
  Circle_Queue shared_queue = Circle_Queue(queue_size);

  //**Create arguments for all producers
  Producer_Arg producer_arg_array[no_of_producers];
  //**Create arguments for all consumers
  Consumer_Arg consumer_arg_array[no_of_consumers];

  //** Create threads for all producers
  for(int i=0; i< no_of_producers; ++i){
    producer_arg_array[i] = Producer_Arg(shared_queue, i+1, no_of_jobs);
    if(pthread_create(&producerid[i], NULL, producer, (void *)&producer_arg_array[i])){
      cout << "Error created producer thread " << i+1 << endl;
      exit(EXIT_FAILURE);
    }
  }

  //** Create threads for all consumers
  for(int i=0; i< no_of_consumers; ++i){
    consumer_arg_array[i] = Consumer_Arg(shared_queue, i+1);
    if(pthread_create(&consumerid[i], NULL, consumer, (void *)&consumer_arg_array[i])){
      cout << "Error created consumer thread " << i+1 << endl;
      exit(EXIT_FAILURE);
    }
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
  int& queue_end_ref = (param->circle_queue)->queue_end;
  Job* new_job;

  //**Edge Case
  if(param->jobs_remaining == 0){
    cout << "Producer(" << param->id << "): No more jobs to generate" << endl;
  }
  
  while(param->jobs_remaining>0){
    if(sem_down(sem_id, SEM_FULL, TIMEOUT_DURATION) < 0){
      cout << "Producer(" << param->id << "): Queue is full. Semaphore operation has timed out" << endl;
      pthread_exit(0);
    }
    sem_wait(sem_id, SEM_MUTEX);
    //**BEGIN CRITICAL REGION
    new_job = new Job(queue_end_ref+1, (rand()%10)+1);
    (param->circle_queue)->push(new_job);
    cout << "Producer(" << param->id << "): " << "Job ID " << new_job->index << " Duration " << new_job->duration << endl;
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
  new_job = NULL; //Deallocate new job to remove dangling pointer
  pthread_exit(0);
}

void *consumer (void *id) 
{
  Consumer_Arg* param = (Consumer_Arg *)id;
  Job current_job;

  while(1){
    if(sem_down(sem_id, SEM_EMPTY, TIMEOUT_DURATION) < 0){
      cout << "Consumer(" << param->id << "): " << "No more jobs left." << endl;
      pthread_exit(0);
    }
    sem_wait(sem_id, SEM_MUTEX);
    //**BEGIN CRITICAL REGION
    current_job = (param->circle_queue)->pop();
    cout << "Consumer(" << param->id << "): " << "Job ID " << current_job.index << " executing sleep duration " << current_job.duration << endl;
 
    //**END CRITICAL REGION
    sem_signal(sem_id, SEM_MUTEX);
    sem_signal(sem_id, SEM_FULL);
    sleep(current_job.duration);
    cout << "Consumer(" << param->id << "): " << "Job ID " << current_job.index << " completed" << endl;
  }
  cout << "outside the while loop" << endl;
  pthread_exit (0);
}
