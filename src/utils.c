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

void    setup_socket(int sockfd) {
    int ttl_val = 64;

    if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) != 0)
        error(ERR_SOCKET, NULL);
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

void    log_verbose(long bytes, char *address, uint16_t seq, int ident, int ttl, float rtt) {
    printf("%ld bytes from %s: icmp_seq=%d ident=%d ttl=%d time=%.1f ms\n",
        bytes, address, seq, ident, ttl, rtt);
}

void    log_regular(long bytes, char *address, uint16_t seq, int ttl, float rtt) {
    printf("%ld bytes from %s: icmp_seq=%d ttl=%d time=%.1f ms\n",
        bytes, address, seq, ttl, rtt);
}

void    print_summary(char *host, int msg_count, int msg_received) {
    printf(BOLD "\n--- %s ping statistics ---\n" RESET, host);
    printf(BLUE "%d packets transmitted," GREEN " %d received," YELLOW " %.6f%% packet loss\n" RESET,
           msg_count, msg_received, ((msg_count - msg_received) / (double)msg_count) * 100.0);
}
