// Error handler

#include "ft_ping.h"

void    packet_warning(t_icmp *icmp_resp)
{
    const char *msg;

    switch (icmp_resp->type) {
        case ICMP_DEST_UNREACH:
            msg = "Destination Unreachable";
            break;
        case ICMP_ECHO:
            msg = "Echo";
            break;
        case ICMP_TIME_EXCEEDED:
            msg = "Time to live exceeded";
            break;
        case ICMP_SOURCE_QUENCH:
            msg = "Source Quench";
            break;
        case ICMP_REDIRECT:
            msg = "Redirect Message";
            break;
        case ICMP_PARAMETERPROB:
            msg = "Parameter Problem";
            break;
        default: // Other unexpected response
            printf(YELLOW "ICMP type=%d code=%d\n" RESET, icmp_resp->type, icmp_resp->code);
            return;
    }
    printf(YELLOW "ft_ping: warning: %s\n" RESET, msg);
}

void    error(t_error err_type, const char *context)
{
    const char *msg;

    switch (err_type) {
        case ERR_SOCKET:
            msg = "Socket error";
            break;
        case ERR_DNS:
            msg = "Name or service not known";
            break;
        case ERR_REVDNS:
            msg = "Could not resolve reverse lookup";
            break;
        case ERR_SEND:
            msg = "Failed to send ICMP packet";
            break;
        case ERR_ARGS:
            msg = "Destination address required";
            break;
        case ERR_INVALID:
            msg = "Invalid argument or missing parameter";
            break;
        case ERR_MEMORY:
            msg = "Memory allocation failed";
            break;
        default:
            msg = "Unknown error";
            break;
    }

    if (context)
        fprintf(stderr, RED "ft_ping: %s: %s\n" RESET, context, msg);
    else
        fprintf(stderr, RED "ft_ping: error: %s\n" RESET, msg);
    gc_collect();

    exit(EXIT_FAILURE);
}
