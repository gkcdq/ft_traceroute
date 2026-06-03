#include "../../lib/traceroute.h"

void printTexte(int n, char *s)
{
    if (n == 1)
    {
        printf("Usage:\n");
        printf("  traceroute [ -46dFITnreAUDV ] host [ packetlen ]\n");
        printf("Options:\n");
        printf("  --help                      Read this help and exit\n");
        return;
    }
    if (n == 2)
    {
        printf("Cannot handle \"packetlen\" cmdline arg `%s\' on position 2 (argc 2)\n", s);
        return;
    }
    if (n == 3)
    {
        printf("Extra arg `%s\' (position 3, argc 3)\n", s);
        return;
    }
    return;
}