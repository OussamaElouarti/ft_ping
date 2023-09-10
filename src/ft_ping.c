#include "../lib/ft_ping.h"

unsigned short checksum(void *b, int len)
{    unsigned short *buf = b;
    unsigned int sum=0;
    unsigned short result;
 
    for ( sum = 0; len > 1; len -= 2 )
        sum += *buf++;
    if ( len == 1 )
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

void    pingTarget(t_args *args)
{
    int sockfd;
    struct sockaddr_in addr_con;
    size_t send;
    struct ping_pkt pckt;
    int addrlen = sizeof(addr_con);
    TargetError(args->target);
    char *ip_addr = dnslookup(args->target, &addr_con);
    if (ip_addr == NULL)
        printf("ft_ping: %s: Name or service not known\n", args->target);
    printf("PING %s (%s):\n", args->target, ip_addr);
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    printf("%d", sockfd);
    int val = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &val, sizeof(val)) < 0)
    {
        printf (" %s \n" ,  strerror(errno));
        exit(0);
    }
    while(LOOP)
    {
        bzero(&pckt, sizeof(pckt));
        pckt.hdr.type = ICMP_ECHO;
        pckt.hdr.un..echo.id = getpid();
         for ( i = 0; i < sizeof(pckt.msg)-1; i++ )
            pckt.msg[i] = i+'0';
         
        pckt.msg[i] = 0;
        pckt.hdr.un.echo.sequence = msg_count++;
        pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));
        send = sendto(sockfd, &pckt, sizeof(pckt), 0)
    }
}