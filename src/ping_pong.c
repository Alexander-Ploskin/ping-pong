#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>

int file_descriptor;
const char* ping_string = "Ping from parent\n";
const char* pong_string = "Pong from child\n";
void print_ping() { write(STDOUT_FILENO, ping_string, strlen(ping_string)); }
void print_pong() { write(STDOUT_FILENO, pong_string, strlen(pong_string)); }

void signalHandler(int signal) { }

void lock()
{
  struct flock fl;
  fl.l_type = F_WRLCK;
  fl.l_whence = SEEK_SET;
  fl.l_start = 0;
  fl.l_len = 0;
  while(fcntl(file_descriptor, F_SETLKW, &fl) != 0) {  }
}

void unlock() {
  struct flock fl;
  fl.l_type = F_UNLCK;
  fl.l_whence = SEEK_SET;
  fl.l_start = 0;
  fl.l_len = 0;
  fcntl(file_descriptor, F_SETLKW, &fl);
}

int main()
{
  signal(SIGUSR1, signalHandler);
  signal(SIGUSR2, signalHandler);

  pid_t pid;
  file_descriptor = open("lockfile", O_CREAT | O_RDWR, 0666);

  switch(pid = fork())
  {
    case -1 : 
      printf("Error during the fork\n");
      exit(1);
    case 0 :
      printf("This process is a child process\n");
      while (true)
      {
        lock();
        sleep(1);
        print_pong();
        unlock();
        kill(pid, SIGUSR1);
        pause();
      }
      exit(0);
    default :
      printf("Forked process PID is %i\n", pid);
      printf("This process is a parent process\n");
      while (true)
      {
        lock();
        sleep(1);
        print_ping();
        unlock();
        kill(pid, SIGUSR2);
        pause();
      }
  }
  return 0;
}
