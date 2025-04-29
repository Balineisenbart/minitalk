

#include "utils.h"

void handler_usr1(int sig, siginfo_t *info, void *ucontext)
{
    (void) ucontext;

    static pid_t client_pid;
    

    client_pid = 0;
    if (!client_pid)
        client_pid = info->si_pid;

    collect_and_print(sig);
}

void setup_signals(void)
{
    struct sigaction sa_usr1;

    sa_usr1.sa_sigaction = handler_usr1;
    sigemptyset(&sa_usr1.sa_mask);
    sa_usr1.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &sa_usr1, NULL);
    sigaction(SIGUSR2, &sa_usr1, NULL);

}

int main(void)
{
    static pid_t    pid;


    pid = getpid();
    printf("SERVER PID: %i\n", pid);

    setup_signals(); 
    
    while (1)
        pause();
    return (1);
}
