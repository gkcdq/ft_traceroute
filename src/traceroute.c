#include "../lib/traceroute.h"

int main(int ac, char **av)
{
    s_info info;
    s_arc arc;

    InformationInit(&info);
    ArcitectureInit(&arc);

    if (checkArgs(ac, av, &arc))
        return arc.exitCode;

    struct addrinfo hints;
    struct addrinfo *res; 

    arc.fd = resolveAndSocket(&arc, &hints, &res);
    if (arc.fd < 0)
        return 1;
    
    //if (send_packet(arc.fd, arc.TTL, res->ai_addr, arc->sequence++) < 0)

    while (arc.TTL <= arc.TTL_MAX)
    {
        printf("%d\n", arc.TTL);

        arc.TTL++;
    }







    freeaddrinfo(res);
    return arc.exitCode;
}