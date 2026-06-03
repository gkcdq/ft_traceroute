#ifndef TRACEROUTE_H
# define TRACEROUTE_H

# define INT_MAX 2147483647


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/cdefs.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>      
#include <netinet/ip_icmp.h>  
#include <unistd.h>
#include <signal.h>
#include <resolv.h>
#include <errno.h>

typedef struct Architecture
{
    int TTL;
    int TTL_MAX;
    int RTT;
    int help;
    char *host;
    int exitCode;
    int fd;
    int sequence;
} s_arc;

typedef struct Information
{
    int family;
    int sockType;
    int protocole;
} s_info;

void PrintHelps();
void ArcitectureInit(s_arc *arc);
void InformationInit(s_info *info);
int checkArgs(int ac, char **av, s_arc *arc);
void printTexte(int n, char *s);
void HintsFilter(struct addrinfo *hints);
int resolveAndSocket(s_arc *arc, struct addrinfo *hints, struct addrinfo **res);
unsigned short calculateChecksum(void *b, int len);
void IcmpInit(struct icmphdr *icmp, int seq);
int send_packet(int sockfd, int ttl, struct sockaddr *target_addr, int seq);

#endif