/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiber <astoiber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:20:44 by astoiber          #+#    #+#             */
/*   Updated: 2025/05/06 00:29:42 by astoiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t	g_shake = 2;

void	morse_message(pid_t server_pid, unsigned char c)
{
	int	i;

	i = 0;
	if (i == 0)
		g_shake = 0;
	else
		g_shake = 1;
	while (i < 8)
	{
		if (((c >> (7 - i)) & 1) == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(200);
		i++;
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGUSR2 && g_shake == 0)
		exit(1);
	else if (sig == SIGUSR2)
	{
		write(STDOUT_FILENO, "acknowledged\n", 14);
		exit(0);
	}
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

int	invalid_input(char **argv)
{
	int	result1;

	result1 = ft_atoi(argv[1]);
	if (result1)
		return (0);
	else
		return (1);
}

void	set_input(void)
{
	struct sigaction	sa_shake;

	sa_shake.sa_handler = signal_handler;
	sa_shake.sa_flags = 0;
	sigemptyset(&sa_shake.sa_mask);
	if (sigaction(SIGUSR1, &sa_shake, NULL) == -1 || sigaction(SIGUSR2,
			&sa_shake, NULL) == -1)
	{
		write(STDERR_FILENO, "sigaction Failed\n", 17);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	int		i;

	if (!(argc == 3) || invalid_input(argv))
	{
		write(STDERR_FILENO,
			"[NOT EXACTlY 3 arguments!\n do: <binary> <PID> <message>]\n", 58);
		exit(EXIT_FAILURE);
	}
	set_input();
	server_pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i] != '\0')
		morse_message(server_pid, argv[2][i++]);
	morse_message(server_pid, '\0');
	while (1)
		pause();
	return (0);
}
