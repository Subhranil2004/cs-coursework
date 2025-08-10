#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024
#define NUM_SERVERS 35

int main()
{
    int sock = 0;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE] = {0};

    FILE *lover_ptr, *hater_ptr;
    lover_ptr = fopen("lovers.txt", "w");
    hater_ptr = fopen("haters.txt", "w");
    if (!lover_ptr || !hater_ptr)
    {
        perror("Couldn't open output files");
        exit(EXIT_FAILURE);
    }

    fputs("Lovers\n", lover_ptr);
    fputs("Haters\n", hater_ptr);

    char *ips[NUM_SERVERS] = {
        "192.168.0.73", "192.168.0.187", "192.168.0.226", "192.168.0.180",
        "192.168.0.216", "192.168.0.43", "192.168.0.98", "192.168.0.57",
        "192.168.0.55", "192.168.0.15", "192.168.0.205", "192.168.0.227",
        "192.168.0.10", "192.168.0.67", "192.168.0.94", "192.168.0.222",
        "192.168.0.19", "192.168.0.172", "192.168.0.230", "192.168.0.14",
        "192.168.0.54", "192.168.0.32", "192.168.0.177", "192.168.0.103",
        "192.168.0.102", "192.168.0.148", "192.168.0.39", "192.168.0.19",
        "192.168.0.232", "192.168.0.38", "192.168.0.12", "192.168.0.217",
        "192.168.0.71", "192.168.0.47", "192.168.0.68"};

    printf("Scanning %d servers...\n", NUM_SERVERS);

    for (int i = 0; i < NUM_SERVERS; i++)
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            perror("Socket creation failed");
            continue;
        }

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, ips[i], &server_addr.sin_addr) <= 0)
        {
            printf("Invalid address: %s\n", ips[i]);
            close(sock);
            continue;
        }

        printf("Connecting to %s... ", ips[i]);

        if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            printf("Failed\n");
            close(sock);
            continue;
        }

        memset(buffer, 0, MAX_BUFFER_SIZE);
        read(sock, buffer, MAX_BUFFER_SIZE);
        printf("Received: %s\n", buffer);

        // Extract ID and behavior
        char id[15], behavior;
        if (sscanf(buffer, "%[^:]:%c", id, &behavior) == 2)
        {
            if (behavior == 'L' || behavior == 'l')
            {
                fprintf(lover_ptr, "%s - %s\n", id, ips[i]);
                printf("\tLOVE\n");
            }
            else if (behavior == 'H' || behavior == 'h')
            {
                fprintf(hater_ptr, "%s - %s\n", id, ips[i]);
                printf("\tHATE\n");
            }
            else
            {
                printf("\tInvalid response format\n");
            }
        }
        else
        {
            printf("\tFailed to parse response\n");
        }

        close(sock); // Close socket after each connection
    }

    fclose(lover_ptr);
    fclose(hater_ptr);

    printf("\nResults saved to lovers.txt & haters.txt\n");

    return 0;
}