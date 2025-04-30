

#include "utils.h"

char *g_final = NULL; 

char *make_string(char *final, char c)
{
    char *temp;
    size_t len;

    len = strlen(final);
    
    temp = malloc (len + 2 * sizeof(char)); //ft_strlen
    if (!temp)
    {
        free(temp);
        exit(EXIT_FAILURE);
    }

    strcpy(temp, final);
    temp[len] = c;
    temp[len + 1] = '\0';

    free(final);
    return (temp);

}

void collect_and_print(int sig)
{
    static unsigned char  c;
    static int            counter;

    if (!g_final)
    {
        g_final = malloc(1);
        if (!g_final)
            exit(EXIT_FAILURE);
        g_final[0] = '\0';
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
        }
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