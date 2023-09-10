#include "../lib/ft_ping.h"

t_args *init(t_args *args)
{
    args = malloc(sizeof(t_args));
    args->size = 0;
    args->verbose = 0;
    args->options = malloc(24);
    args->target = NULL;
    return args;
}

void    help()
{
    printf("Usage: ping [OPTION... ] HOST ...\nSend ICMP ECHO_REQUEST packets to network hosts.\n\nOptions:\n\n -?, --help                 give this help list\n     --usage                give a short usage message\n -v, --verbose              verbose output\n");
}


void    ft_free(t_args *args)
{
    for (int i = 0; i<args->size; i++)
        free(args->options[i]);
    free(args->options);
    if (args->target != NULL)
        free(args->target);
}
