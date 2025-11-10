// Error handler

#include "ft_ping.h"

void    error(t_error err_type, const char *context)
{
    const char *msg;

    switch (err_type)
    {
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
            msg = "Invalid argument";
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
