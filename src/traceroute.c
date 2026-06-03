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

    if (resolveAndSocket(&arc, &hints, &res) == INT_MAX)
        return 1;











    freeaddrinfo(res);
    return arc.exitCode;
}