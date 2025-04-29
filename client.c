


#include "utils.h"

void morse_message(pid_t server_pid, char *message)
{
    unsigned char   c;
    int             i;

    i = 0;
    while(message)
    {
        c = (unsigned char) *message++;
        while(i < 8)
        {
            if (((c >> i) & 1) == 0)
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

    pid = (pid_t)ft_atoi(pid_argument);
    return pid;
}

int main(int argc, char **argv)
{
    pid_t   server_pid;
    char    *message;

    if (!(argc == 2) || invalid_input(argv))
        exit(EXIT_FAILURE);

    message = argv[2];
    server_pid = handle_pid(argv[1]);

    morse_message(server_pid, message);
    while (1)
        pause();

    return (0);
}
