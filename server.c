

#include "utils.h"

void handler_usr1(int sig, siginfo_t *info, void *ucontext)
{
    (void) ucontext;

    static pid_t client_pid;
    
    if (!client_pid)
        client_pid = info->si_pid;

    collect_and_print(sig);
}

void handle_sigint(int sig)
{
    (void)sig;
    printf("\n[Server shutting down on SIGINT]\n");

    if (g_final)
    {
        free(g_final);
        g_final = NULL;
    }

    exit(0);
}

void setup_signals(void)
{
    struct sigaction sa_usr1;

    sa_usr1.sa_sigaction = handler_usr1;
    sigemptyset(&sa_usr1.sa_mask);
    sa_usr1.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &sa_usr1, NULL);
    sigaction(SIGUSR2, &sa_usr1, NULL);
    if (sigaction(SIGUSR1, &sa_usr1, NULL) == -1 || sigaction(SIGUSR2, &sa_usr1, NULL) == -1)
    {
        printf("sigaction Failed");
        exit(EXIT_FAILURE);
    }

    struct sigaction sa_int;

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("sigaction SIGINT");
        exit(EXIT_FAILURE);
    }
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
