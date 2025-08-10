#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>

#define PORT 12345
#define BUFFER_SIZE 1024
#define BROADCAST_IP "192.168.0.255"

int main()
{
    int sock;
    struct sockaddr_in broadcast_addr, server_addr;
    char buffer[BUFFER_SIZE];

    FILE *lover_ptr = fopen("lovers.txt", "w");
    FILE *hater_ptr = fopen("haters.txt", "w");

    if (!lover_ptr || !hater_ptr)
    {
        perror("File creation failed");
        exit(EXIT_FAILURE);
    }

    fputs("Lovers\n", lover_ptr);
    fputs("Haters\n", hater_ptr);

    int lovers = 0, haters = 0;

    // Create socket (UDP)
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Enable broadcast
    int broadcast = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
    {
        perror("Broadcast enabling failed");
        exit(EXIT_FAILURE);
    }

    // Configure broadcast address
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

    // Send broadcast message
    char *message = "Your teaching";
    sendto(sock, message, strlen(message), 0, (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr));
    printf("Broadcast message sent to %s\n", BROADCAST_IP);

    socklen_t server_addr_len = sizeof(server_addr);

    // Wait for multiple responses
    fd_set fds;
    struct timeval tv;
    FD_ZERO(&fds);
    FD_SET(sock, &fds);
    tv.tv_sec = 10; // 2 seconds timeout
    tv.tv_usec = 0;

    while (select(sock + 1, &fds, NULL, NULL, &tv) > 0)
    {
        memset(buffer, 0, BUFFER_SIZE);
        recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &server_addr_len);

        // Parse the server response
        char *id = strtok(buffer, ":");
        char *response = strtok(NULL, ":");

        if (response)
        {
            char server_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &server_addr.sin_addr, server_ip, INET_ADDRSTRLEN);
            if (strstr(response, "L") != NULL || strstr(response, "l") != NULL)
            {
                fprintf(lover_ptr, "IP: %s | ID: %s\n", server_ip, id);
                lovers++;
                printf("%s (%s): LOVE\n", id, server_ip);
            }
            else if (strstr(response, "H") != NULL || strstr(response, "h") != NULL)
            {
                fprintf(hater_ptr, "IP: %s | ID: %s\n", server_ip, id);
                haters++;
                printf("%s (%s): HATE\n", id, server_ip);
            }
            else
            {
                printf("%s (%s): Invalid msg\n", id, server_ip);
            }
        }
    }

    fclose(lover_ptr);
    fclose(hater_ptr);
    close(sock);

    printf("\nFinal Count:\n");
    printf("Lovers: %d\n", lovers);
    printf("Haters: %d\n", haters);

    return 0;
}