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

int sem_close (int id)
{
  if (semctl (id, 0, IPC_RMID, 0) < 0)
    return -1;
  return 0;
}

Job::Job(){}
Job::Job(int index, int dur):index(index+1), duration(dur){}

void signal_handler(int signum){
  exit(signum);
}

void exit_function(){
  sem_close(sem_id);
}

Arg::Arg(vector<Job>&queue, int id):queue(&queue), id(id){};

Arg::~Arg(){
  cout << "Argument destructor called" << endl;
}

Consumer_Arg::Consumer_Arg(vector<Job>&queue,int &start_pos,int id):Arg(queue, id), queue_start_pos(&start_pos){};

Consumer_Arg::~Consumer_Arg(){
  cout << "Consumer Argument destructor called" << endl;
}

Producer_Arg::Producer_Arg(vector<Job>&queue, int &end_pos,int id, int job_total): Arg(queue, id), queue_end_pos(&end_pos), jobs_remaining(job_total){};

Producer_Arg::~Producer_Arg(){
  cout << "Producer Argument destructor called" << endl;
}

