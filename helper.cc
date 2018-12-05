/******************************************************************
 * The helper file that contains the following helper functions:
 * check_arg - Checks if command line input is a number and returns it
 * sem_create - Create number of sempahores required in a semaphore array
 * sem_init - Initialise particular semaphore in semaphore array
 * sem_wait - Waits on a semaphore (akin to down ()) in the semaphore array
 * sem_signal - Signals a semaphore (akin to up ()) in the semaphore array
 * sem_close - Destroy the semaphore array
 ******************************************************************/

# include "helper.h"

int check_arg (char *buffer)
{
  int i, num = 0, temp = 0;
  if (strlen (buffer) == 0)
    return -1;
  for (i=0; i < (int) strlen (buffer); i++)
  {
    temp = 0 + buffer[i];
    if (temp > 57 || temp < 48)
      return -1;
    num += pow (10, strlen (buffer)-i-1) * (buffer[i] - 48);
  }
  return num;
}

int sem_create (key_t key, int num)
{
  int id;
  if ((id = semget (key, num,  0666 | IPC_CREAT | IPC_EXCL)) < 0)
    return -1;
  return id;
}

int sem_init (int id, int num, int value)
{
  union semun semctl_arg;
  semctl_arg.val = value;
  if (semctl (id, num, SETVAL, semctl_arg) < 0)
    return -1;
  return 0;
}

void sem_wait (int id, short unsigned int num)
{
  struct sembuf op[] = {
    {num, -1, SEM_UNDO}
  };
  semop (id, op, 1);
}

void sem_signal (int id, short unsigned int num)
{
  struct sembuf op[] = {
    {num, 1, SEM_UNDO}
  };
  semop (id, op, 1);
}

int sem_down(int id, short unsigned int num, int timeout_value){
  struct sembuf op[] = {
    {num, -1, SEM_UNDO}
  };

  struct timespec timeout{
    (time_t) timeout_value,
    0,
  };

  if(semtimedop(id,op,1,&timeout) < 0) {
    if(errno != EAGAIN){
      cerr << "Error executing semaphore instruction" << endl;
    }
    return -1;
  }
  return 0;
}

int sem_close (int id)
{
  if (semctl (id, 0, IPC_RMID, 0) < 0)
    return -1;
  return 0;
}

Job::Job(){};
Job::Job(int index, int dur):index(index), duration(dur){}
Job::~Job(){};

Job Circle_Queue::pop(){
  Job temp = *(queue[queue_start]);
  queue[queue_start]->~Job();
  queue[queue_start] = NULL;
  if(++queue_start > int(queue.capacity()-1)) queue_start = 0;
  return temp;
}

void Circle_Queue::push(Job* new_job){
  queue[queue_end] = new_job;
  if(++queue_end > int(queue.capacity()-1)) queue_end = 0;
}

Circle_Queue::Circle_Queue(int size):queue{}, queue_start(0), queue_end(0){
  queue.resize(size, nullptr);
}

Circle_Queue::~Circle_Queue(){
  //** queue clean up if exitted abnormally
  for(vector<Job*>::size_type i=0; i!=queue.size();++i){
    if (queue[i] != NULL){
      delete queue[i];
      queue[i] = NULL;
    }
  }
}

void signal_handler(int signum){
  exit(signum);
}

void exit_function(){
  sem_close(sem_id);
}

Consumer_Arg::Consumer_Arg(){};
Consumer_Arg::Consumer_Arg(Circle_Queue& queue,int id):circle_queue(& queue), id(id){};

Producer_Arg::Producer_Arg(){};
Producer_Arg::Producer_Arg(Circle_Queue& queue, int id, int job_total): Consumer_Arg(queue, id), jobs_remaining(job_total){};

