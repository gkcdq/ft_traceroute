#include "../../lib/traceroute.h"

void ArcitectureInit(s_arc *arc)
{
    arc->TTL = 0;
    arc->TTL_MAX = 0;
    arc->RTT = 0;
    arc->help = 0;
    arc->host = NULL;
    arc->exitCode = 0;
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