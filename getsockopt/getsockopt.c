#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

/**
 * Check opening and getsockopt sockets
 * Run only as root
 */

size_t
strlcpy(char *dst, const char *src, size_t siz)
{
    char *d = dst;
    const char *s = src;
    size_t n = siz;

    /* Copy as many bytes as will fit */
    if (n != 0 && --n != 0)
    {
        do
        {
            if ((*d++ = *s++) == 0)
                break;
        } while (--n != 0);
    }

    /* Not enough room in dst, add NUL and traverse rest of src */
    if (n == 0)
    {
        if (siz != 0)
            *d = '\0'; /* NUL-terminate dst */
        while (*s++)
            ;
    }

    return (s - src - 1); /* count does not include NUL */
}

void get_sock_opt(const int sock, const char *nf_table_name)
{
    if (sock < 0){
        printf("Error: %s\n", strerror(errno));
        return;
    }

    struct ipt_getinfo info;
    memset(&info, 0, sizeof(info));
    strlcpy(info.name, nf_table_name, sizeof(info.name));
    socklen_t len = sizeof(info);

    if (getsockopt(sock, IPPROTO_IP, IPT_SO_GET_INFO, &info, &len) < 0)
    {
        printf("getsockopt error: %s\n", strerror(errno));
        return;
    }

    printf("info {\n name:%s\n num_entries:%i\n size:%i\n underflow:%i\n valid_hooks:%i\n}\n",
           info.name, info.num_entries, info.size, info.underflow, info.valid_hooks);
}

int main()
{
    // Only sudo
    // RAW socket
    int so_raw = -1;
    so_raw = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

    // UDP socket
    // int so_udp = -1;
    // so_udp = socket(AF_INET, SOCK_DGRAM, 0);

const char *table_name = "conntrack";

    get_sock_opt(so_raw, table_name);
    // get_sock_opt(so_udp, table_name);

    close(so_raw);
    // close(so_udp);
    return 0;
}