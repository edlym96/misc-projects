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
  if(argc != 5){
    cout << "Incorrect number of input parameters!" << endl;
    return 0;
  }

  key_t sem_key = SEM_KEY;
  //  int parameter = 5;
  int queue_size = atoi(argv[1]);
  int no_of_jobs = atoi(argv[2]);
  int no_of_producers = atoi(argv[3]);
  int no_of_consumers = atoi(argv[4]);
  pthread_t producerid[no_of_producers];
  pthread_t consumerid[no_of_consumers];
  
  vector<Job*> circle_queue; // shared queue
  circle_queue.resize(queue_size, nullptr);
  int queue_end = 0; //variables to keep track of queue position
  int queue_start = 0;

  //Consider changing this to statically allocated to remove need for explicit destructors
  Producer_Arg* producer_arg_array[no_of_producers];
  //**Create threads for all producers
  for(int i=0; i< no_of_producers; ++i){
    producer_arg_array[i] = new Producer_Arg(circle_queue, queue_end, i+1, no_of_jobs);
    pthread_create(&producerid[i], NULL, producer, (void *)producer_arg_array[i]);
  }

  Consumer_Arg* consumer_arg_array[no_of_consumers];
  //**Create threads for all consumers
  for(int i=0; i< no_of_consumers; ++i){
    consumer_arg_array[i] = new Consumer_Arg(circle_queue, queue_start,i+1);
    pthread_create(&consumerid[i], NULL, consumer, (void *)consumer_arg_array[i]);
  }

  sem_id = sem_create(sem_key, NO_OF_SEMAPHORES);

  signal(SIGHUP, signal_handler);
  signal(SIGABRT, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGTSTP, signal_handler);
  signal(SIGTERM, signal_handler);
  signal(SIGKILL, signal_handler);
  signal(SIGSEGV, signal_handler);
  atexit(exit_function);
  
  cout << sem_id << endl;
  if(sem_id < 0) exit(EXIT_FAILURE);
  if(sem_init(sem_id, SEM_MUTEX, 1)) exit(EXIT_FAILURE);
  if(sem_init(sem_id, SEM_FULL, queue_size)) exit(EXIT_FAILURE);
  if(sem_init(sem_id, SEM_EMPTY, 0)) exit(EXIT_FAILURE);

  
  for(int i=0; i<no_of_producers; ++i){
    if(pthread_join (producerid[i], NULL)){
      cout << "error joining thread" << endl;
      exit(EXIT_FAILURE);
    }
  }

  for(int i=0; i<no_of_consumers; ++i){
    if(pthread_join (consumerid[i], NULL)){
      cout << "error joining thread" << endl;
      exit(EXIT_FAILURE);
    }
  }

  for(int i=0; i<no_of_producers; ++i){
    producer_arg_array[i]->~Producer_Arg();
  }

  for(int i=0; i<no_of_producers; ++i){
    consumer_arg_array[i]->~Consumer_Arg();
  }

  for(vector<Job*>::size_type i=0; i!=circle_queue.size();++i){
    if (circle_queue[i] != NULL){
      circle_queue[i]->~Job();
      circle_queue[i] = NULL;
    }
  }
  
  sem_close(sem_id);
  return 0;
}

void *producer (void *parameter) 
{
  // TODO
  Producer_Arg* param = (Producer_Arg *)parameter;
  srand((int)time(0));
  vector<Job*>& queue_ref = *(param->queue);
  int& queue_end_ref = *(param->queue_end_pos);
  Job new_job;
  while(param->jobs_remaining>0){
    sem_wait(sem_id, SEM_FULL);
    sem_wait(sem_id, SEM_MUTEX);
    queue_ref[queue_end_ref] = new Job(queue_end_ref, (rand()%10)+1);
    cout << "Producer(" << param->id << "): " << "Job ID " << queue_ref[queue_end_ref]->index << " Duration " << queue_ref[queue_end_ref]->duration << endl;
    //**return queue position to start of queue once out of range
    if(++queue_end_ref > int(queue_ref.capacity()-1)) queue_end_ref=0;
    sem_signal(sem_id, SEM_MUTEX);
    sem_signal(sem_id, SEM_EMPTY);
    (param->jobs_remaining)--;
  }
  pthread_exit(0);
}

void *consumer (void *id) 
{
    // TODO
  Consumer_Arg* param = (Consumer_Arg *)id;
  vector<Job*>& queue_ref = *(param->queue);
  int& queue_start_ref = *(param->queue_start_pos);
  Job current_job;

  while(1){
    sem_wait(sem_id, SEM_EMPTY);
    sem_wait(sem_id, SEM_MUTEX);
    current_job = *(queue_ref[queue_start_ref]);
    queue_ref[queue_start_ref]->~Job();
    queue_ref[queue_start_ref] = NULL;
    sem_signal(sem_id, SEM_MUTEX);
    sem_signal(sem_id, SEM_FULL);
    if(++queue_start_ref > int(queue_ref.capacity()-1)) queue_start_ref = 0;
    cout << "Consumer(" << param->id << "): " << "Job ID " << current_job.index << " executing sleep duration " << current_job.duration << endl;
    sleep(current_job.duration);
  }
  
  pthread_exit (0);

}
