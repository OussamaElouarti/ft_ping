#ifndef FT_PING_H
#define FT_PING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

#define PING_PKT_S 64


typedef struct s_args
{
    char **options;
    int size;
    char *target;
    int verbose;
}               t_args;

struct ping_pkt
{
    struct icmphdr hdr;
    char msg[PING_PKT_S-sizeof(struct icmphdr)];
};

t_args *init(t_args *args);
void    help(void);
void    intHandler(int dummy);
void    ft_free(t_args *args);
void    pingTarget(t_args *args);
void TargetError(char *target);
char    *dnslookup(char *host, struct sockaddr_in *addr_con);


#endif
