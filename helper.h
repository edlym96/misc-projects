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
using namespace std;

# define SEM_KEY 1497 // Change this number as needed
# define SEM_MUTEX 0
# define SEM_FULL 1
# define SEM_EMPTY 2

extern int sem_id;

union semun {
  int val;               /* used for SETVAL only */
  struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
  ushort *array;         /* used for GETALL and SETALL */
};

struct Job{
  int index;
  int duration;
  Job();
  Job(int index, int dur);
};

struct Arg{
  vector<Job> *queue;
  int id;

  Arg(vector<Job>&queue, int id);
  ~Arg();
};

struct Consumer_Arg : public Arg{
  int *queue_start_pos;
  Consumer_Arg(vector<Job>&queue,int &start_pos,int id);
  ~Consumer_Arg();
};

struct Producer_Arg : public Arg{
  int *queue_end_pos;
  int jobs_remaining;
  Producer_Arg(vector<Job>&queue, int &end_pos,int id, int job_total);
  ~Producer_Arg();
};

int check_arg (char *);
int sem_create (key_t, int);
int sem_init (int, int, int);
void sem_wait (int, short unsigned int);
void sem_signal (int, short unsigned int);
int sem_close (int);
void signal_handler(int signum);
void exit_function();
#endif
