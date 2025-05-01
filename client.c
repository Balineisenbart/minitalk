


#include "utils.h"

volatile sig_atomic_t shake_received = 0;

void handle_shake(int sig)
{
        (void)sig;
        shake_received = 1;
        
}

void setup_shake_handler(void)
{
    struct sigaction sa_shake;

    sa_shake.sa_handler = handle_shake;
    sigemptyset(&sa_shake.sa_mask);
    sa_shake.sa_flags = SA_RESTART;

    if (sigaction(SIGUSR1, &sa_shake, NULL) == -1)
    {
        printf("sigaction SIGINT");
        exit(EXIT_FAILURE);
    }
}

void morse_message(pid_t server_pid, char *message)
{
    unsigned char   c;
    int             i;

    while (*message)
    {
        c = (unsigned char)*message++;
        i = 0;

        // Send each bit of the character
        while (i < 8)
        {
            if (((c >> (7 - i)) & 1) == 0)
                kill(server_pid, SIGUSR1);
            else
                kill(server_pid, SIGUSR2);
            i++;
            usleep(50);
        }

        // Wait for server's ACK
        shake_received = 0;
        write(1, "[client] waiting for ACK...\n", 29);
        while (!shake_received)
            pause();
        write(1, "[client] got ACK\n", 18);
    }

    // Send null terminator ('\0') to mark end of message
    write(1, "[client] sending null terminator\n", 33);
    i = 0;
    while (i < 8)
    {
        kill(server_pid, SIGUSR1); // 8 bits of 0
        i++;
        usleep(50);
    }

    shake_received = 0;
    write(1, "[client] waiting for final ACK...\n", 34);
    while (!shake_received)
        pause();
    write(1, "[client] exiting after final ACK\n", 34);
}

pid_t handle_pid(char *pid_argument)
{
    pid_t pid;

    pid = (pid_t)atoi(pid_argument);//ft_atoi
    return pid;
}

int main(int argc, char **argv)
{
    pid_t   server_pid;

    if (!(argc == 3) || invalid_input(argv))
    {
        printf("[NOT EXACTlY 3 arguments!\n do: <binary> <PID> <message>]");
        exit(EXIT_FAILURE);
    }
    setup_shake_handler();

    server_pid = handle_pid(argv[1]);
    morse_message(server_pid, argv[2]);
    return (0);
}
