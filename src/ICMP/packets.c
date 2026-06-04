#include "../../lib/traceroute.h"

int send_packet(int sockfd, int ttl, struct sockaddr *target_addr, int seq)
{
    struct icmphdr icmp;

    IcmpInit(&icmp, seq);

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

int receive_packet(s_arc *arc)
{
    arc->addr_len = sizeof(arc->recv_addr);
    arc->bytes_received = recvfrom(arc->fd, arc->buffer, sizeof(arc->buffer), 0, (struct sockaddr *)&arc->recv_addr, &arc->addr_len);
    return 0;
} 

int parse_reply(char *buffer, int my_pid)
{
    struct iphdr *ip = (struct iphdr *)buffer;
    int ip_header_len = ip->ihl * 4; 
    struct icmphdr *icmp = (struct icmphdr *)(buffer + ip_header_len);
    if (icmp->type == ICMP_TIME_EXCEEDED) 
    {
        struct iphdr *inner_ip = (struct iphdr *)(buffer + ip_header_len + 8);
        int inner_ip_hlen = inner_ip->ihl * 4;
        struct icmphdr *inner_icmp = (struct icmphdr *)(buffer + ip_header_len + 8 + inner_ip_hlen);
        if (ntohs(inner_icmp->un.echo.id) != (my_pid & 0xFFFF))
            return -1; 
        return 0; 
    }
    else if (icmp->type == ICMP_ECHOREPLY) 
    {
        if (ntohs(icmp->un.echo.id) != (my_pid & 0xFFFF))
            return -1; 

        return 1; 
    }

    return -1; 
}