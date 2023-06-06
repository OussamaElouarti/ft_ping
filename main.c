#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

int loop = 1;

typedef struct s_args
{
    char **options;
    int size;
    char *target;
    int verbose;
}               t_args;

t_args *init(t_args *args)
{
    args = malloc(sizeof(t_args));
    args->size = 0;
    args->verbose = 0;
    args->options = malloc(24);
    return args;
}

void    help()
{
    printf("Usage\n ping [options] <destination>\n\nOptions:\n  <destination>      dns name or ip address\n  -h                 print help and exit\n  -v                 verbose output\n");
}

void    intHandler(int dummy)
{
    loop = 0;
    return ;
}

void    ft_free(t_args *args)
{
    for (int i = 0; i<args->size; i++)
        free(args->options[i]);
    free(args->options);
    if (args->target != NULL)
        free(args->target);
}

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
        if (!strcmp("-h", args->options[i]))
            help();
        else if (!strcmp("-v", args->options[i]))
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

void    pingTarget(t_args *args)
{
    int sockfd;
    struct sockaddr_in addr_con;
    int addrlen = sizeof(addr_con);
    TargetError(args->target);
    char *ip_addr = dnslookup(args->target, &addr_con);
    if (ip_addr == NULL)
        printf("ft_ping: %s: Name or service not known\n", args->target);
    printf("%s\n", ip_addr);
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    printf("%d", sockfd);
    int val = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &val, sizeof(val)) < 0)
    {
        printf (" %s \n" ,  strerror(errno));
        exit(0);
    }
    ÷
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
        pingTarget(args);
    }
    ft_free(args);
    return 0;
}