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

// char    *rev_dns_lookup(char *ip_addr) {
//     t_ipaddr        temp_addr;
//     unsigned int    len;
//     char            buf[NI_MAXHOST], *ret_buf;

//     ft_bzero(&temp_addr, sizeof(t_ipaddr));
//     temp_addr.sin_family = AF_INET;
//     if (inet_pton(AF_INET, ip_addr, &temp_addr.sin_addr) <= 0)
//         error(ERR_REVDNS, ip_addr);
//     len = sizeof(t_ipaddr);
//     if (getnameinfo((t_sockaddr *)&temp_addr, len, buf, sizeof(buf), NULL, 0, NI_NAMEREQD))
//         error(ERR_REVDNS, ip_addr);
//     ret_buf = (char *)gc_malloc((ft_strlen(buf) + 1) * sizeof(char));
//     if (!ret_buf)
//         error(ERR_MEMORY, NULL);
//     ft_strcpy(ret_buf, buf);

//     return ret_buf;
// }
