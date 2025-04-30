


#include "utils.h"

void morse_message(pid_t server_pid, char *message)
{
    unsigned char   c;
    int             i;

    while(*message)
    {
        c = (unsigned char) *message++;
        i = 0;
        while(i < 8)
        {
            if (((c >> (7 - i)) & 1) == 0)
                kill(server_pid, SIGUSR1);
            else
                kill(server_pid, SIGUSR2);
            i++;
            usleep(50);
        }
    }
    i = 0;
    while (i < 8)
    {
        kill(server_pid, SIGUSR1);
        i++;
        usleep(50);
    }
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
    server_pid = handle_pid(argv[1]);
    morse_message(server_pid, argv[2]);
    return (0);
}
