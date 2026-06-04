#include "../../lib/traceroute.h"

extern int SIG;

void handleSignal(int sig)
{
    (void)sig;
    SIG = 1;
}