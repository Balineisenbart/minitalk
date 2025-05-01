



#ifndef UTILS_H
#define     UTILS_H

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <stdio.h> //dont forget to remove!!!!!!!

extern char *g_final;
extern volatile sig_atomic_t shake_received;


int	ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);


void setup_signals(void);
void handler_usr1(int sig, siginfo_t *info, void *context);
int invalid_input(char **argv);
pid_t handle_pid(char *pid_argument);
void collect_and_print(int sig, pid_t client_pid);
void morse_message(pid_t server_pid, char *message);


#endif