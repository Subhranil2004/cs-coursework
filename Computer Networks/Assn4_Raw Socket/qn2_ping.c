#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

unsigned short checksum(unsigned short *addr, int len);

int main(int argc, char *argv[])
{
    int len, ip_len, n;
    char buff[1024];
    struct ip *iphdr;
    struct icmp *icmphdr;
    int sockfd;
    struct addrinfo hints, *res;
    struct sockaddr_in raddr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    /* Check arguments */
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <ip_address>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Create raw socket */
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
    {
        perror("Socket error: You must run as root");
        exit(EXIT_FAILURE);
    }

    /* Resolve target IP */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; // Use only IPv4
    hints.ai_socktype = SOCK_RAW;

    if ((n = getaddrinfo(argv[1], NULL, &hints, &res)) != 0)
    {
        fprintf(stderr, "Error in getaddrinfo(): %s\n", gai_strerror(n));
        exit(EXIT_FAILURE);
    }

    /* Prepare ICMP echo request */
    memset(buff, 0, sizeof(buff));
    icmphdr = (struct icmp *)buff;
    icmphdr->icmp_type = ICMP_ECHO;
    icmphdr->icmp_code = 0;
    icmphdr->icmp_id = getpid() & 0xFFFF; // Use process ID as identifier
    icmphdr->icmp_seq = 1;
    len = sizeof(struct icmp);
    icmphdr->icmp_cksum = 0;
    icmphdr->icmp_cksum = checksum((unsigned short *)icmphdr, len);

    /* Send the packet */
    if (sendto(sockfd, buff, len, 0, res->ai_addr, res->ai_addrlen) == -1)
    {
        perror("sendto() error");
        exit(EXIT_FAILURE);
    }

    /* Wait for reply */
    memset(buff, 0, sizeof(buff));

    if (recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&raddr, &addr_len) == -1)
    {
        perror("recvfrom() error");
        exit(EXIT_FAILURE);
    }

    /* Parse reply */
    iphdr = (struct ip *)buff;
    ip_len = iphdr->ip_hl << 2;
    icmphdr = (struct icmp *)(buff + ip_len);

    if (icmphdr->icmp_type == ICMP_ECHOREPLY)
        printf("%s is alive.\n", argv[1]);
    else
        printf("%s is not responding.\n", argv[1]);

    printf("Message received from %s\n", inet_ntoa(raddr.sin_addr));

    /* Cleanup */
    freeaddrinfo(res);
    close(sockfd);
    return 0;
}

/* ICMP checksum function */
unsigned short checksum(unsigned short *addr, int len)
{
    int sum = 0;
    unsigned short answer = 0;
    unsigned short *w = addr;

    while (len > 1)
    {
        sum += *w++;
        len -= 2;
    }

    /* Handle odd byte */
    if (len == 1)
    {
        *(unsigned char *)(&answer) = *(unsigned char *)w;
        sum += answer;
    }

    /* Fold 32-bit sum to 16-bit */
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}