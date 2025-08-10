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
#include <sys/time.h>
#include <errno.h>

#define PACKET_SIZE 64
#define MAX_PINGS 5 // Number of ICMP requests to send
#define TIMEOUT 2   // Timeout in seconds

unsigned short checksum(unsigned short *addr, int len);
double time_diff(struct timeval *start, struct timeval *end);

int main(int argc, char *argv[])
{
    int sockfd, ttl = 64, sent = 0, received = 0;
    struct addrinfo hints, *res;
    struct sockaddr_in raddr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    char buff[PACKET_SIZE];

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

    /* Set TTL */
    if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
    {
        perror("Failed to set TTL");
        exit(EXIT_FAILURE);
    }

    /* Resolve target IP */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;

    if (getaddrinfo(argv[1], NULL, &hints, &res) != 0)
    {
        fprintf(stderr, "Error resolving IP address\n");
        exit(EXIT_FAILURE);
    }

    printf("Pinging %s with %d bytes of data:\n", argv[1], PACKET_SIZE);

    for (int i = 1; i <= MAX_PINGS; i++)
    {
        struct icmp *icmphdr;
        struct timeval start, end;

        /* Prepare ICMP echo request */
        memset(buff, 0, PACKET_SIZE);
        icmphdr = (struct icmp *)buff;
        icmphdr->icmp_type = ICMP_ECHO;
        icmphdr->icmp_code = 0;
        icmphdr->icmp_id = getpid() & 0xFFFF;
        icmphdr->icmp_seq = i;
        icmphdr->icmp_cksum = 0;
        icmphdr->icmp_cksum = checksum((unsigned short *)icmphdr, PACKET_SIZE);

        /* Get send time */
        gettimeofday(&start, NULL);

        /* Send ICMP packet */
        if (sendto(sockfd, buff, PACKET_SIZE, 0, res->ai_addr, res->ai_addrlen) == -1)
        {
            perror("sendto() error");
            continue;
        }
        sent++;

        /* Set receive timeout */
        struct timeval tv;
        tv.tv_sec = TIMEOUT;
        tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

        /* Wait for reply */
        memset(buff, 0, PACKET_SIZE);
        if (recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&raddr, &addr_len) == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                printf("Request timed out.\n");
            else
                perror("recvfrom() error");
            continue;
        }

        /* Get receive time */
        gettimeofday(&end, NULL);
        received++;

        /* Compute RTT */
        double rtt = time_diff(&start, &end);

        /* Print results */
        printf("Reply from %s: bytes=%d time=%.2f ms TTL=%d\n",
               inet_ntoa(raddr.sin_addr), PACKET_SIZE, rtt, ttl);

        sleep(1); // Wait before sending the next packet
    }

    /* Print summary */
    printf("\n--- %s ping statistics ---\n", argv[1]);
    printf("%d packets transmitted, %d received, %.2f%% packet loss\n",
           sent, received, ((sent - received) / (double)sent) * 100);

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

/* Calculate time difference in milliseconds */
double time_diff(struct timeval *start, struct timeval *end)
{
    return ((end->tv_sec - start->tv_sec) * 1000.0) + ((end->tv_usec - start->tv_usec) / 1000.0);
}