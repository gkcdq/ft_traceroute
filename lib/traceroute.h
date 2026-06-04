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
    double RTT;
    int help;
    char *host;
    int exitCode;
    int fd;
    int sequence;
    char buffer[1024];
    int probe;
    ssize_t bytes_received;

    struct sockaddr_in recv_addr;
    socklen_t addr_len;
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
int ft_strcmp(char *s1, char *s2);
int checkArgs(int ac, char **av, s_arc *arc);
char *ft_strcpy(char *dest, const char *src);
void printTexte(int n, char *s);
void HintsFilter(struct addrinfo *hints);
int resolveAndSocket(s_arc *arc, struct addrinfo *hints, struct addrinfo **res);
unsigned short calculateChecksum(void *b, int len);
void IcmpInit(struct icmphdr *icmp, int seq);
int send_packet(int sockfd, int ttl, struct sockaddr *target_addr, int seq);
int receive_packet(s_arc *arc);
int parse_reply(char *buffer, int my_pid);

#endif