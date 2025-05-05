/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiber <astoiber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:20:50 by astoiber          #+#    #+#             */
/*   Updated: 2025/05/05 22:46:49 by astoiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

void	handle_full_byte(pid_t *current_client, unsigned char *message, int *c, int *bit_counter)
{
	if (message[*c] == '\0')
	{
		write(STDOUT_FILENO, message, *c);
		write(STDOUT_FILENO, "\n", 1);
		kill(*current_client, SIGUSR2);
		ft_memset(message, 0, sizeof(unsigned char) * 2097152);
		*c = 0;
        *current_client = 0;
	}
	else
	{
		//kill(*current_client, SIGUSR1);
		(*c)++;
	}
	*bit_counter = 0;
}


void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int				bit_counter;
	static int				c;
	static pid_t			current_client;
	static unsigned char	message[2097152];

	(void) ucontext;
    if (!current_client)
       current_client = info->si_pid;
    else if (current_client != info->si_pid)
        kill(info->si_pid, SIGUSR2);
    message[c] |= (sig == SIGUSR2) << (7 - bit_counter);
    
    //kill(current_client, SIGUSR1);
    if (kill(current_client, SIGUSR1) == -1)
    {
        current_client = 0;
        bit_counter = 0;
        c = 0;
        ft_memset(message, 0, sizeof(2097152));
        return ;
    }
    bit_counter++;
	if (bit_counter == 8)
		handle_full_byte(&current_client, message, &c, &bit_counter);
}


int	main(void)
{
	struct sigaction	sa_sig;

	write(STDOUT_FILENO, "SERVER PID:\n", 12);
	putnbr(getpid());
	write(STDOUT_FILENO, "\n", 1);
	ft_memset(&sa_sig, 0, sizeof(sa_sig));
	sa_sig.sa_sigaction = signal_handler;
	sa_sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_sig.sa_mask);
	if (sigaction(SIGUSR1, &sa_sig, NULL) == -1 || sigaction(SIGUSR2, &sa_sig,
			NULL) == -1)
    {
		write(STDERR_FILENO, "sigaction Failed\n", 17);
		exit(EXIT_FAILURE);
    }
    while (1)
		pause();
	return (0);
}