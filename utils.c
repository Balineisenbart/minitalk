

#include "utils.h"

char *make_string(char *final, char c)
{
    char *temp;
    int   i;
    
    temp = malloc (ft_strlen(final) + 2 * sizeof(char));
    if (!temp)
    {
        free(temp);
        exit(EXIT_FAILURE);
    }
    i = 0;
    while(final[i] != '\0')
    {
        temp[i] = final[i];
        i++;
    }
    temp[i++] = c;
    temp[i] = '\0';

    free(final);
    return (temp);
}

void collect_and_print(int sig)
{
    static unsigned char  c;
    static int            counter;
    static char           *final;

    counter = 0;
    if (!final)
        final = "";


    c |= (sig == SIGUSR2) << (7 - counter);

    counter++;
    if (counter == 8)
    {
        final = make_string(final, c);
        if (c == '\0')
        {
            printf("%s \n", final);
            free(final);
        }
        counter = 0;
    }
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