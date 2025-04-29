


#include "utils.h"

void morse_message(pid_t server_pid, char *message)
{
    unsigned char   c;
    int             i;
    int             j;

    i = 0;
    j = 0;
    while(message[j] != '\0') //?pointer arithmetic??
    {
        c = (unsigned char) message[j];
        while(i < 8)
        {
            if (((c >> i) & 1) == 0)
                kill(server_pid, SIGUSR1);
            else
                kill(server_pid, SIGUSR2);
            i++;
            usleep(50);
        }
        j++;
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

    pid = (pid_t)ft_atoi(pid_argument);
    return pid;
}

int main(int argc, char **argv)
{
    pid_t   server_pid;

    if (!(argc == 3) || invalid_input(argv)) //how to check for correct PID?
        exit(EXIT_FAILURE);


    server_pid = handle_pid(argv[1]);

    morse_message(server_pid, argv[2]);

    /*while (1)
        pause();*/
    return (0);
}
