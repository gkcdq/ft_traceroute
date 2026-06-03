#include "../../lib/traceroute.h"

static int ft_strcmp(char *s1, char *s2)
{
    int i = 0;

    while(s1[i])
    {
        if (s1[i] != s2[i])
            return 1;
        i++;
    }
    return 0;
}

int checkArgs(int ac, char **av, s_arc *arc)
{
    (void)av;
    (void)arc;
    if (ac < 2)
        return (printTexte(1, ""), 1);
    int i = 0;
    while(av[i])
    {
        if (ft_strcmp(av[i], "--help") == 0)
            return (printTexte(1, ""), 1);
        i++;
    }
    if (ac == 3)
        return (printTexte(2, av[2]), arc->exitCode = 2, 1);
    if (ac > 3)
        return (printTexte(3, av[3]), arc->exitCode = 2, 1);
    if (ac == 2)
        arc->host = av[1];
    return 0;
}