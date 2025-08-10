#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main()
{
    int sock = 0;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE] = {0};

    while (1)
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        memset(&server_addr, '0', sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);

        char server_ip[16];
        int num = rand() % 256;
        snprintf(server_ip, sizeof(server_ip), "192.168.0.%d", num); // Convert num to string
        // snprintf(server_ip, sizeof(server_ip), "192.168.0.216"); // Convert num to string
        printf("Trying to connect to ip: %s...", server_ip);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) < 0)
        {
            printf("Invalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            printf("Connection Failed for ip: %s\n", server_ip);
            // IMP! If a connection fails, the client should create a new socket before retrying.
            close(sock);
            continue;
        }
        // connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

        read(sock, buffer, MAX_BUFFER_SIZE);
        printf("Server message: %s", buffer);

        // search LOVE in buffer if found break
        if (strstr(buffer, "L") != NULL || strstr(buffer, "l") != NULL)
        {
            printf("\tLOVE\n");
            printf("Found LOVE\n");
            // close(sock);
            break;
        }
        else if (strstr(buffer, "H") != NULL || strstr(buffer, "h") != NULL)
        {
            printf("\tHATE\n");
        }
        else
        {
            printf("\tInvalid message\n");
        }
        // sleep(1);
    }
    close(sock);

    return 0;
}