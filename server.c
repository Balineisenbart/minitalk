

#include "utils.h"

void handler_usr1(int sig, siginfo_t *info, void *ucontext)
{
    (void) ucontext;
    static pid_t client_pid;
    

    client_pid = 0;
    if (!client_pid)
        client_pid = info->si_pid;

    collect_and_print(sig);
    kill(client_pid, SIGUSR1);


}

void setup_signals(void)
{
    struct sigaction sa_usr1;
    //struct sigaction sa_usr2;

    //for SIGUSR1 block SIGUSR2
    sa_usr1.sa_sigaction = handler_usr1;
    sigemptyset(&sa_usr1.sa_mask);
    sigaddset(&sa_usr1.sa_mask, SIGUSR2);
    sa_usr1.sa_flags = SA_SIGINFO;

    /*//for SIGUSR2 block SIGUSR1
    sa_usr2.sa_sigaction = handler_usr2;
    sigemptyset(&sa_usr2.sa_mask);
    sigaddset(&sa_usr2.sa_mask, SIGUSR1);
    sa_usr2.sa_flags = SA_SIGINFO;
*/
    sigaction(SIGUSR1, &sa_usr1, NULL);
    sigaction(SIGUSR2, &sa_usr2, NULL);

}

int main(void)
{
    static pid_t    pid;


    pid = getpid();
    printf("SERVER PID: %i\n", pid); //how to include ft_printf

    setup_signals(); 
    
    while (1)
        pause();
}
