

#include "utils.h"



//----the idea is tht when server receives SIGUSR1 it adds 0 to the binary 'c', 1 when it receives SIGUSR2.
//----at the same time when receiving a signal it blocks the othersignal, or ques it.
//----when 'c' is 8 elements long, it gets printed ->but needs conversion to ASCII



void handler_usr2(int sig, siginfo_t *info, void *ucontext)
{
    (void)ucontext;
    static pid_t client_pid;


    client_pid = 0;

    //--------handshake------------//do i need to send back? what to do with that--client needs to pause?
    if(!client_pid)
        client_pid = info->si_pid;
    kill(client_pid, SIGUSR2); //thats part of the handshake but what happens @client?

    //---------print output---------
    collect_and_print(sig);

}

char convert_to_dec(int binary)
{
    int i;
    int res;
    int dec;
    char c;

    i = 0;
    res = 0;
    dec = 0;
    while (binary)
    {
        res = binary % 10;
        dec += res << i;
        binary /= 10;
        i++;
    }
    c = dec;
    return (c);
}

char *make_string(char *final, char c)
{
    char *temp;
    
    temp = malloc (ft_strlen(final) + 2 * sizeof(char));
    if (!temp)
    {
        free(temp);
        exit(EXIT_FAILURE);
    }
    while(final)
    {
        temp = final++;
        temp++;
    }
    temp += c;
    temp += '\0';

    return (temp);
}

void collect_and_print(int sig)
{
    static unsigned int   c;
    static int            counter;
    static char           *final;
    char                  character;

    c = 0;
    counter = 0;
    if (!final)
        final = "";

    if (sig == SIGUSR1)
        c = c * 10 + 0;
    else
        c = c * 10 + 1;

    counter++;
    if (counter == 8)
    {
        character = convert_to_dec(c);
        final = make_string(final, c);
        if (character == '\0')
        {
            printf("%s \n", final);
            free(final);//?? from make string
        }
        counter = 0;
        c = 0;    
    }
}

int invalid_input(char **argv)
{
    int result1;
    //int result2;

    result1 = ft_atoi(argv[1]);
    //result2 = ft_isprint(argv[2]); //enough to check?

    if (result1)
        return (1);
    else
        return (0);
}