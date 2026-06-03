#include "../../lib/traceroute.h"

int send_packet(int sockfd, int ttl, struct sockaddr *target_addr, int seq)
{
    struct icmphdr icmp;

    IcmpInit(icmp, seq);

    if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
    {
        fprintf(stderr, "Error: setsockopt TTL failed\n");
        return -1;
    }

    if (sendto(sockfd, &icmp, sizeof(icmp), 0, target_addr, sizeof(*target_addr)) < 0)
    {
        fprintf(stderr, "Error: sendto failed\n");
        return -1;
    }
    return 0;
}