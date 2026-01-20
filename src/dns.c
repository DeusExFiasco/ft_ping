// DNS related functions

#include "ft_ping.h"

char    *dns_lookup(const char *host, t_ipaddr *address_cont) {
    struct addrinfo hints, *res;
    char *ip = (char *)gc_malloc(INET_ADDRSTRLEN);
    if (!ip)
        error(ERR_MEMORY, NULL);

    ft_bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    if (getaddrinfo(host, NULL, &hints, &res) != 0)
        error(ERR_DNS, host);

    t_ipaddr *addr = (t_ipaddr *)res->ai_addr;
    if (inet_ntop(AF_INET, &addr->sin_addr, ip, INET_ADDRSTRLEN) == NULL) {
        gc_free(ip);
        freeaddrinfo(res);
        error(ERR_DNS, host);
    }
    ft_memcpy(address_cont, addr, sizeof(t_ipaddr));
    address_cont->sin_port = htons(PORT_NUMBER);
    freeaddrinfo(res);

    return ip;
}
