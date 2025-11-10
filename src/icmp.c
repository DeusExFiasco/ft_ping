// ICMP packet related functions

#include "ft_ping.h"

void    build_icmp_request(t_icmp *icmp_hdr, unsigned int seq_no, pid_t pid) {
    t_time  tv_start;

    ft_bzero(icmp_hdr, PING_PACKET_SIZE);
    icmp_hdr->type = ICMP_ECHO;
    icmp_hdr->code = 0;
    icmp_hdr->un.echo.id = htons(pid & 0xFFFF);
    icmp_hdr->un.echo.sequence = htons(seq_no);
    gettimeofday(&tv_start, NULL);
    ft_memcpy((char *)icmp_hdr + sizeof(t_icmp), &tv_start, sizeof(tv_start));
    icmp_hdr->checksum = 0;
    icmp_hdr->checksum = checksum(icmp_hdr, PING_PACKET_SIZE);
}

ssize_t send_icmp_request(int sockfd, t_ipaddr *addr, char *packet) {
    ssize_t sent = sendto(sockfd, packet, PING_PACKET_SIZE, 0,
                          (t_sockaddr *)addr, sizeof(*addr));
    if (sent <= 0)
        error(ERR_SEND, NULL);
    return sent;
}

ssize_t receive_icmp_reply(int sockfd, t_ipaddr *r_addr, char *recv_buf) {
    struct iovec    iov;
    struct msghdr   msg;
    char            control[512];

    iov.iov_base = recv_buf;
    iov.iov_len = 1024;

    ft_bzero(&msg, sizeof(msg));
    msg.msg_name = r_addr;
    msg.msg_namelen = sizeof(*r_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = control;
    msg.msg_controllen = sizeof(control);

    ssize_t recvd = recvmsg(sockfd, &msg, 0);
    return recvd;
}
