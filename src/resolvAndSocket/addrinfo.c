#include "../../lib/traceroute.h"

int resolveAndSocket(s_arc *arc, struct addrinfo *hints, struct addrinfo **res)
{
    HintsFilter(hints);
    if (getaddrinfo(arc->host, NULL, hints, res) != 0)
    {
        fprintf(stderr, "Erreur de résolution");
        return -1;
    }
    int sockfd = socket(hints->ai_family, hints->ai_socktype, hints->ai_protocol);
    if (sockfd < 0)
    {
        fprintf(stderr, "Error : can't open a socket\n");
        freeaddrinfo(*res);
        return -1;
    }
    return sockfd;
}