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
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    struct addrinfo *res; 

    arc.fd = resolveAndSocket(&arc, &hints, &res);
    if (arc.fd < 0)
    {
        return 1;
    }
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    if (setsockopt(arc.fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        fprintf(stderr, "Error: setsockopt timeout failed\n");
        freeaddrinfo(res);
        return 1;
    }

    struct timeval start, end;
    char target_ip_str[INET_ADDRSTRLEN] = {0};
    
    if (res && res->ai_addr) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
        inet_ntop(AF_INET, &(ipv4->sin_addr), target_ip_str, INET_ADDRSTRLEN);
    }

    printf("traceroute to %s (%s), %d hops max, %d byte packets\n", 
            (arc.host ? arc.host : av[1]), target_ip_str, arc.TTL_MAX, 60);

    // DÉCLARATION ICI : prev_ip doit être ici pour être persistante sur toute la route
    char prev_ip[INET_ADDRSTRLEN] = {0};

    while (arc.TTL <= arc.TTL_MAX)
    {
        printf("%2d", arc.TTL);
        
        for(arc.probe = 0; arc.probe < 3; arc.probe++)
        {
            gettimeofday(&start, NULL);
            if (send_packet(arc.fd, arc.TTL, res->ai_addr, arc.sequence++) < 0)
            {
                freeaddrinfo(res);
                return 1;
            }

            int res_type = -1;
            while (1) 
            {
                receive_packet(&arc);
                gettimeofday(&end, NULL);

                if (arc.bytes_received < 0) {
                    res_type = -2;
                    break;
                }

                res_type = parse_reply(arc.buffer, getpid());
                if (res_type >= 0) break;
            }

            if (res_type == -2) 
            {
                printf("  *");
            } 
            else 
            {
                arc.RTT = (double)(end.tv_sec - start.tv_sec) * 1000.0 + (double)(end.tv_usec - start.tv_usec) / 1000.0;
                char ip_str[INET_ADDRSTRLEN] = {0};
                inet_ntop(AF_INET, &(arc.recv_addr.sin_addr), ip_str, INET_ADDRSTRLEN);

                if (ft_strcmp(prev_ip, ip_str) != 0) 
                {
                    char hostname[NI_MAXHOST] = {0};
                    if (getnameinfo((struct sockaddr *)&arc.recv_addr, arc.addr_len, hostname, sizeof(hostname), NULL, 0, 0) != 0) 
                    {
                        ft_strcpy(hostname, ip_str);
                    }
                    printf(" %s (%s)", hostname, ip_str);
                    ft_strcpy(prev_ip, ip_str);
                }
                printf("  %.3f ms", arc.RTT);
                
                if (res_type == 1)
                {
                    arc.TTL = arc.TTL_MAX; 
                    break;
                }
            }
            fflush(stdout);
        }        
        printf("\n");
        arc.TTL++;
    }
    freeaddrinfo(res);
    return arc.exitCode;
}