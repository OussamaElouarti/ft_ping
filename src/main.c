#include "../lib/ft_ping.h"

void    parse_args(char **input, t_args *args, int ac)
{
    for (int i=1; i < ac; i++)
    {
        if (input[i][0] == '-' && strlen(input[i])>1 && input[i][1] != '-')
        {
            args->options[args->size] = strdup(input[i]);
            args->size++;
        }
        else
        {
            if (args->target != NULL)
                free(args->target);
            args->target = strdup(input[i]);
        }
    }
}

void    Executeoptions(t_args *args)
{
    for (int i = 0; i<args->size; i++)
    {
        if (!strcmp("-?", args->options[i]))
            help();
        else if (!strcmp("-v", args->options[i]))
            if (args->target == NULL)
                printf("ping: missing host operand\nTry 'ping --help' or 'ping --usage' for more information.\n");
            else
                args->verbose = 1;
        else
        {
            printf("ft_ping: invalid option -- \'%c\'\n\n", args->options[i][1]);
            help();
        }
    }
}

void TargetError(char *target)
{
    if (!strcmp("--",target))
    {
        printf("ft_ping: usage error: Destination address required\n");
        exit(1);
    }
    else if (!strncmp("---", target, 3))
    {
        printf("ft_ping: invalid option -- \'%c\'\n\n", target[2]);
        help();
        exit(1);
    }
}

char    *dnslookup(char *host, struct sockaddr_in *addr_con)
{
    struct hostent *host_entity;
    struct addrinfo *info;
    char *ip=(char*)malloc(NI_MAXHOST*sizeof(char));
    int i;

    //no ip found for hostname
    if (getaddrinfo(host, NULL, NULL, &info))
        return NULL;
     
    //filling up address structure
    addr_con = (struct sockaddr_in *) info->ai_addr;
    inet_ntop(AF_INET, &(addr_con->sin_addr), ip, INET_ADDRSTRLEN);
    return (ip);
}

int     main(int ac, char** av)
{
    t_args *args = init(args);

    signal(SIGINT, intHandler);
    if (ac == 1)
        printf("ft_ping: usage error: Destination address required\n");
    else if (ac > 1)
    {
        parse_args(av, args, ac);
        Executeoptions(args);
        if (args->target != NULL)
            pingTarget(args);
    }
    ft_free(args);
    return 0;
}