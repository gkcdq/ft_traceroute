#include "../../lib/traceroute.h"

void ArcitectureInit(s_arc *arc)
{
    arc->TTL = 1;
    arc->TTL_MAX = 30;
    arc->RTT = 0;
    arc->help = 0;
    arc->host = NULL;
    arc->exitCode = 0;
    arc->fd = -1;
    arc->sequence = 1;
}

void InformationInit(s_info *info)
{
    info->family = 0;
    info->sockType = 0;
    info->protocole = 0;
}

void HintsFilter(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_RAW;
    hints->ai_protocol = IPPROTO_ICMP;
}

void IcmpInit(struct icmphdr *icmp, int seq)
{
    memset(icmp, 0, sizeof(*icmp));
    icmp->type = ICMP_ECHO;            
    icmp->code = 0;                  
    icmp->un.echo.id = htons(getpid() & 0xFFFF);
    icmp->un.echo.sequence = htons(seq);
    icmp->checksum = 0; 
    icmp->checksum = calculateChecksum(&icmp, sizeof(icmp));
}
