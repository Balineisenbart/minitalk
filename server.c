

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	putnbr(int n)
{
	char	c;

	if (n == -2147483648)
		write(STDOUT_FILENO, "-2147483648", 12);
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		putnbr(n / 10);
		c = (n % 10 + '0');
		write(STDOUT_FILENO, &c, 1);
	}
	if (n < 10)
	{
		c = (n % 10 + '0');
		write(STDOUT_FILENO, &c, 1);
	}
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}

void signal_handler(int sig, siginfo_t *info, void *ucontext)
{
    static int  bit_counter;
    static int  c;
    static pid_t current_client;
    static unsigned char message[2097152];

    (void) ucontext;

    if (!current_client)
        current_client = info->si_pid;
    else if (current_client != info->si_pid)
         return;
    //add kill 0?
    //add timeout for silent client to avoid zombie server -- wait 1s or so

    message[c] |= (sig == SIGUSR2) << (7 - bit_counter);
    bit_counter++;
    if (bit_counter == 8)
    {
        if (message[c] == '\0')
        {
            write(STDOUT_FILENO, &message, c);
            write(STDOUT_FILENO, "\n", 1);
            kill(info->si_pid, SIGUSR2);
            c = 0;
            bit_counter = 0;
            ft_memset(message, 0, sizeof(message));
        }
        else
        {
            kill(info->si_pid, SIGUSR1);
            bit_counter = 0;
            c++;
        }
    }
}

int main(void)
{
    struct sigaction sa_sig;

    write(STDOUT_FILENO, "SERVER PID:\n", 12);
    putnbr(getpid());
    write(STDOUT_FILENO, "\n", 1);

    ft_memset(&sa_sig, 0, sizeof(sa_sig));
    sa_sig.sa_sigaction = signal_handler;
    sa_sig.sa_flags = SA_SIGINFO;
    sigemptyset(&sa_sig.sa_mask);
    sigaddset(&sa_sig.sa_mask, SIGUSR1);
    sigaddset(&sa_sig.sa_mask, SIGUSR2);
    
    if (sigaction(SIGUSR1, &sa_sig, NULL) == -1 || sigaction(SIGUSR2, &sa_sig, NULL) == -1)
    {
        write(STDERR_FILENO, "sigaction Failed\n", 17);
        exit(EXIT_FAILURE);
    }

    while(1)
        pause();

    return (0);
}