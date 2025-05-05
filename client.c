

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

volatile sig_atomic_t g_shake = 1;

void shake_handler(int sig)
{
    if (sig == SIGUSR1)
        g_shake = 1;
    else if (sig == SIGUSR2)
    {
        g_shake = 1;
		write(STDOUT_FILENO, "acknowledged\n", 14);
    }
}

void morse_message(pid_t server_pid, unsigned char c)
{
    int i;

    i = 0;
    g_shake = 0;
    while (i < 8)
    {
        if (((c >> (7 - i)) & 1) == 0)
            kill(server_pid, SIGUSR1);
        else
            kill(server_pid, SIGUSR2);
        i++;
        usleep(200);
    }
    if (!g_shake)
        pause();
}


int	ft_atoi(const char *str)
{
	unsigned long	number;
	int				i;
	int				sign;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (1);
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + str[i++] - '0';
		if (sign == 1 && number >= 9223372036854775807)
			return (-1);
		else if (sign == -1 && number >= (unsigned long)9223372036854775807 + 1)
			return (0);
	}
	return ((int)number * sign);
}

int invalid_input(char **argv)
{
    int result1;

    result1 = ft_atoi(argv[1]);

    if (result1)
        return (0);
    else
        return (1);
}

int main(int argc, char **argv)
{
    struct sigaction sa_shake;
    pid_t   server_pid;
    int i;

    if (!(argc == 3) || invalid_input(argv))
    {
        write(STDERR_FILENO, "[NOT EXACTlY 3 arguments!\n do: <binary> <PID> <message>]\n", 58);
        exit(EXIT_FAILURE);
    }
    
    sa_shake.sa_handler = shake_handler;
    sa_shake.sa_flags = 0;
    sigemptyset(&sa_shake.sa_mask);
    sigaddset(&sa_shake.sa_mask, SIGUSR2);

    if (sigaction(SIGUSR1, &sa_shake, NULL) == -1 || sigaction(SIGUSR2, &sa_shake, NULL) == -1)
    {
        write(STDERR_FILENO, "sigaction SIGINT\n", 17);
        exit(EXIT_FAILURE);
    }

    server_pid = ft_atoi(argv[1]);
    i = 0;
    while (argv[2][i] != '\0')
        morse_message(server_pid, argv[2][i++]);
    morse_message(server_pid, '\0');
    return (0);
}