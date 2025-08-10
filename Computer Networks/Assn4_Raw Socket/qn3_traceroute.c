#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>

#define MAX_HOPS 30
#define PACKET_SIZE 64
#define TIMEOUT 2

// Function to calculate the checksum
unsigned short checksum(void *buf, int len)
{
    unsigned short *data = buf;
    unsigned int sum = 0;
    while (len > 1)
    {
        sum += *data++;
        len -= 2;
    }
    if (len == 1)
    {
        sum += *(unsigned char *)data;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (unsigned short)~sum;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *dest_ip = argv[1];
    struct sockaddr_in dest_addr;

    dest_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, dest_ip, &dest_addr.sin_addr) != 1)
    {
        perror("Invalid IP address");
        exit(EXIT_FAILURE);
    }

    int send_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (send_sock < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int ttl = 1;
    char send_buf[PACKET_SIZE];
    char recv_buf[PACKET_SIZE];

    struct sockaddr_in recv_addr;
    socklen_t addr_len = sizeof(recv_addr);

    printf("Tracing route to %s:\n", dest_ip);

    while (ttl <= MAX_HOPS)
    {
        setsockopt(send_sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));

        // Prepare ICMP packet
        memset(send_buf, 0, PACKET_SIZE);
        struct icmphdr *icmp = (struct icmphdr *)send_buf;
        icmp->type = ICMP_ECHO;
        icmp->code = 0;
        icmp->un.echo.id = getpid();
        icmp->un.echo.sequence = ttl;
        icmp->checksum = checksum(send_buf, PACKET_SIZE);

        // Send the packet
        if (sendto(send_sock, send_buf, PACKET_SIZE, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
        {
            perror("Send failed");
            break;
        }

        // Set timeout for receiving ICMP response
        struct timeval tv;
        tv.tv_sec = TIMEOUT;
        tv.tv_usec = 0;
        setsockopt(send_sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

        // Receive the ICMP response
        int bytes_received = recvfrom(send_sock, recv_buf, PACKET_SIZE, 0, (struct sockaddr *)&recv_addr, &addr_len);

        if (bytes_received > 0)
        {
            char router_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &recv_addr.sin_addr, router_ip, sizeof(router_ip));
            printf("%2d  %s\n", ttl, router_ip);

            // Check if we've reached the destination
            if (strcmp(router_ip, dest_ip) == 0)
            {
                printf("Reached destination\n");
                break;
            }
        }
        else
        {
            printf("%2d  *\n", ttl); // Timeout, no response
        }

        ttl++;
    }

    close(send_sock);
    return 0;
}