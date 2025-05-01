

#include "utils.h"

char *g_final = NULL; 

char *make_string(char *final, char c)
{
    char *temp;
    size_t len;

    len = strlen(final);
    
    temp = malloc((len + 2) * sizeof(char));
    if (!temp)
        exit(EXIT_FAILURE);

    strcpy(temp, final);
    temp[len] = c;
    temp[len + 1] = '\0';

    free(final);
    return (temp);

}

void collect_and_print(int sig, pid_t client_pid)
{
    static unsigned char  c;
    static pid_t   current_client;
    static int            counter;

    if (!current_client)
        current_client = client_pid;
    else if (current_client != client_pid)
         return;

    if (!g_final)
    {
        g_final = malloc(1);
        if (!g_final)
            exit(EXIT_FAILURE);
        g_final[0] = '\0';
        current_client = client_pid;

    }

    c |= (sig == SIGUSR2) << (7 - counter);
    counter++;
    if (counter == 8)
    {
        g_final = make_string(g_final, c);
        if (c == '\0')
        {
            printf("%s\n", g_final);
            free(g_final);
            g_final = NULL;
            current_client = 0;
        }
        kill(client_pid, SIGUSR1);
        counter = 0;
        c = 0;
    }
}


int invalid_input(char **argv)
{
    int result1;

    result1 = atoi(argv[1]); //ft_atoi

    if (result1)
        return (0);
    else
        return (1);
}