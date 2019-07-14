/******************************************************************
 * Header file for the helper functions. This file includes the
 * required header files, as well as the function signatures and
 * the semaphore values (which are to be changed as needed).
 ******************************************************************/

# ifndef HELPER_H
# define HELPER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/time.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <ctype.h>
# include <iostream>
# include <vector>
# include <csignal>
# include <string>
using namespace std;

# define SEM_KEY 1497 // Change this number as needed
# define SEM_MUTEX 0
# define SEM_FULL 1
# define SEM_EMPTY 2
# define TIMEOUT_DURATION 20

extern int sem_id;

union semun {
  int val;               /* used for SETVAL only */
  struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
  ushort *array;         /* used for GETALL and SETALL */
};

//Data Structure for Jobs
struct Job{
  int index;
  int duration;
  Job();
  Job(int index, int dur);
  ~Job();
};

//Data structure for circle queue
struct Circle_Queue{
  vector<Job*> queue;
  int queue_start;
  int queue_end;
  Job pop();
  void push(Job* new_job);
  Circle_Queue(int size);
  ~Circle_Queue();
};

//Data structure for argument to be passed to consumer function
struct Consumer_Arg{
  Circle_Queue* circle_queue;
  int id;
  Consumer_Arg();
  Consumer_Arg(Circle_Queue& queue, int id);
};

//Data structure for argument to be passed to producer function
struct Producer_Arg : public Consumer_Arg{
  int jobs_remaining;
  Producer_Arg();
  Producer_Arg(Circle_Queue& queue, int id, int job_total);
};

int check_arg (char *);
int sem_create (key_t, int);
int sem_init (int, int, int);
void sem_wait (int, short unsigned int);
int sem_down(int id, short unsigned int num, int timeout_value);
void sem_signal (int, short unsigned int);
int sem_close (int);
void signal_handler(int signum);
void exit_function();
#endif
