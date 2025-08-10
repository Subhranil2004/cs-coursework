#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>

#define BUFFER_SIZE 65536

void process_packet(unsigned char *buffer, int size);

int main()
{
    int sock_raw;
    unsigned char buffer[BUFFER_SIZE];

    // Create raw socket to capture all incoming packets
    sock_raw = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock_raw < 0)
    {
        perror("Socket Error");
        return 1;
    }

    printf("Packet Sniffer Started...\n");

    while (1)
    {
        struct sockaddr saddr;
        socklen_t saddr_size = sizeof(saddr);

        // Receive packets
        int data_size = recvfrom(sock_raw, buffer, BUFFER_SIZE, 0, &saddr, &saddr_size);
        if (data_size < 0)
        {
            perror("Recvfrom Error");
            break;
        }

        // Process received packet
        process_packet(buffer, data_size);
    }

    close(sock_raw);
    return 0;
}

void process_packet(unsigned char *buffer, int size)
{
    struct iphdr *ip_header = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    struct sockaddr_in source, dest;

    struct in_addr source_ip;
    source_ip.s_addr = ip_header->saddr;

    // Convert source and destination IPs
    source.sin_addr.s_addr = ip_header->saddr;
    dest.sin_addr.s_addr = ip_header->daddr;

    // printf("\nPacket Received: ");
    // printf("Source: %s, ", inet_ntoa(source.sin_addr));
    // printf("Destination: %s, ", inet_ntoa(dest.sin_addr));

    // Identify protocol
    char *protocoltype;
    switch (ip_header->protocol)
    {
    case IPPROTO_TCP:
    {
        // struct tcphdr *tcp_header = (struct tcphdr *)(buffer + sizeof(struct ethhdr) + ip_header->ihl * 4);
        // printf("Protocol: TCP, ");
        protocoltype = "TCP";
        // printf("Src Port: %u, Dest Port: %u\n", ntohs(tcp_header->source), ntohs(tcp_header->dest));
        break;
    }
    case IPPROTO_UDP:
    {
        // struct udphdr *udp_header = (struct udphdr *)(buffer + sizeof(struct ethhdr) + ip_header->ihl * 4);
        // printf("Protocol: UDP, ");
        protocoltype = "UDP";
        // printf("Src Port: %u, Dest Port: %u\n", ntohs(udp_header->source), ntohs(udp_header->dest));
        break;
    }
    case IPPROTO_ICMP:
    {
        // printf("Protocol: ICMP\n");
        protocoltype = "ICMP";
        break;
    }
    default:
        printf("Protocol: Other (%d)\n", ip_header->protocol);
        break;
    }

    printf("Packet Type: %s, Source IP: %s\n", protocoltype, inet_ntoa(source_ip));
}