// Miscellanious project utils

#include "ft_ping.h"

void    display_help(void) {
    printf(
BOLD "Usage\n" RESET
"ping [options] <destination>\n\
\n"
BOLD "Options\n" RESET
"<destination>      DNS name or IP address\n\
-f                 flood ping\n\
-q                 quiet output\n\
-v                 verbose output\n\
-?                 print help and exit\n"
    );
}

u_int16_t   checksum(void *b, int len) {
    u_int16_t  *buf = b;
    u_int32_t  sum = 0;
    u_int16_t  result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    result = ~sum;

    return result;
}

char    *dns_lookup(const char *host, t_ipaddr *address_cont) {
    struct addrinfo hints, *res;
    char *ip = malloc(INET_ADDRSTRLEN);
    if (!ip)
        error(ERR_MEMORY, NULL);

    ft_bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    if (getaddrinfo(host, NULL, &hints, &res) != 0)
        error(ERR_DNS, host);

    t_ipaddr *addr = (t_ipaddr *)res->ai_addr;
    if (inet_ntop(AF_INET, &addr->sin_addr, ip, INET_ADDRSTRLEN) == NULL) {
        free(ip);
        freeaddrinfo(res);
        error(ERR_DNS, host);
    }
    ft_memcpy(address_cont, addr, sizeof(t_ipaddr));
    address_cont->sin_port = htons(PORT_NUMBER);
    freeaddrinfo(res);

    return ip;
}

char    *rev_dns_lookup(char *ip_addr) {
    t_ipaddr        temp_addr;
    unsigned int    len;
    char            buf[NI_MAXHOST], *ret_buf;

    ft_bzero(&temp_addr, sizeof(t_ipaddr));
    temp_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip_addr, &temp_addr.sin_addr) <= 0)
        error(ERR_REVDNS, ip_addr);
    len = sizeof(t_ipaddr);
    if (getnameinfo((t_sockaddr *)&temp_addr, len, buf, sizeof(buf), NULL, 0, NI_NAMEREQD))
        error(ERR_REVDNS, ip_addr);
    ret_buf = (char *)malloc((ft_strlen(buf) + 1) * sizeof(char));
    if (!ret_buf)
        error(ERR_MEMORY, NULL);
    ft_strcpy(ret_buf, buf);

    return ret_buf;
}
