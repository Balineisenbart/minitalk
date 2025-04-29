



#ifndef UTILS_H
#define     UTILS_H

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h> //dont forget to remove!!!!!!!

int	ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);


void setup_signals(void);
void handler_usr1(int sig, siginfo_t *info, void *context);
int invalid_input(char **argv);
pid_t handle_pid(char *pid_argument);
void collect_and_print(int sig);
void morse_message(pid_t server_pid, char *message);


#endif