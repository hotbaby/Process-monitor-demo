#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

typedef enum SIG_FLAGS
{
    SIGNAL_CHILD = 0x1,
}SIG_FLGS_t;

unsigned int signal_flags = 0;

void sig_handler_cb (int singal)
{
    if (singal == SIGCHLD)
    {
        fprintf(stderr, "receive Child stopped or terminated singal.\n");
        signal_flags |= SIGNAL_CHILD;
    }

    return;
}

void restart_process(int argc, char **argv)
{
    pid_t pid;

    if (argc < 1)
    {
        fprintf(stderr, "%s params error.\n", __func__);
        return;
    }

    fprintf(stderr, "restart prsocess.\n");
    
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "fork error.\n");
        assert(0);
    }
    else if (pid == 0) // child process
    {
        //char *newargv[] = {NULL};
        char **newargv = &argv[1];
        char **newenv = {NULL};
        execve(argv[0], newargv, newenv);
    }

    return;
}

int main(int argc, char **argv)
{
    pid_t pid;

    if (argc < 2)
    {
        fprintf(stderr, "params error\n.");
        return -1;
    }

    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "fork error.\n");
        assert(0);
    }
    else if (pid == 0) // child process
    {
        char **newargv = &argv[2];
        char **newenv = {NULL};
        execve(argv[1], newargv, newenv);
    }

    //parent process
    signal(SIGCHLD, sig_handler_cb);

    int newargc = --argc;
    char **newargv = &argv[1];
    struct timeval timeout;
    while(1)
    {
        timeout.tv_sec = 0;
        timeout.tv_usec = 20000;
        select(0, 0, 0, 0, &timeout);

        if (signal_flags & SIGNAL_CHILD)
        {
            //restart process
            wait(NULL);
            restart_process(newargc, newargv);
            signal_flags &= ~SIGNAL_CHILD;
        }
    }

    return 0;
}
