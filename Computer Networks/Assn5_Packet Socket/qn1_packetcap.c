#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>

void packet_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes)
{
    printf("Captured a packet with length of [%u] bytes. ", (unsigned)h->len);

    struct ip *ip_header = (struct ip *)(bytes + 14); // Skip Ethernet header (14 bytes)
    // printf("Source IP: %s\n", inet_ntoa(ip_header->ip_src));
    // printf("Destination IP: %s\n", inet_ntoa(ip_header->ip_dst));

    switch (ip_header->ip_p)
    {
    case IPPROTO_TCP:
        printf("Protocol: TCP\n");
        break;
    case IPPROTO_UDP:
        printf("Protocol: UDP\n");
        break;
    case IPPROTO_ICMP:
        printf("Protocol: ICMP\n");
        break;
    default:
        printf("Protocol: Other\n");
        break;
    }
    // empty buffer explicitly
    fflush(stdout);
}

int main()
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs, *device;

    // Find all devices
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr, "Error finding devices: %s\n", errbuf);
        return 1;
    }

    // Use the first available device
    device = alldevs;
    if (!device)
    {
        fprintf(stderr, "No devices found.\n");
        return 1;
    }

    printf("Using device: %s\n", device->name);

    // Open the device in promiscuous mode
    pcap_t *handle = pcap_open_live(device->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL)
    {
        fprintf(stderr, "Could not open device %s: %s\n", device->name, errbuf);
        return 1;
    }

    // Start capturing packets
    pcap_loop(handle, -1, packet_handler, NULL); // capture packets indefinitely

    // Cleanup
    pcap_close(handle);
    pcap_freealldevs(alldevs);

    return 0;
}