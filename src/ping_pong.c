#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    if(fork())
    {
        printf("pr1");
        prinf(getpid());
        int f = open("/tmp/file.txt", O_RDWR | O_CREAT, 0666);
        flock(f, LOCK_SH);
        pause();
        exit(0);
    }
    else
    {
        printf("pr2");
        prinf(getpid());
        int f = open("/tmp/file.txt", O_RDWR);
        flock(f, LOCK_EX);
        printf("Ok!");
        exit(0);
    }
    return 0;
}