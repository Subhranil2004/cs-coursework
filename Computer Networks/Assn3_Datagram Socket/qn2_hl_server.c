#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <time.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main()
{
    char *ID = "2022ITB012";
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create socket (UDP)
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to the specified port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Set server behavior: HATER or LOVER
    srand(time(NULL));
    char *identity = (rand() % 100 < 80) ? "H" : "L";

    printf("Server is running on port %d as a %s...\n", PORT, identity);

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);

        // Receive broadcast message from client
        recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);

        if (strcmp(buffer, "Your teaching") == 0)
        {
            printf("Received message: %s\n", buffer);

            // Send back response with ID
            snprintf(buffer, BUFFER_SIZE, "%s:%s", ID, identity);
            sendto(server_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, client_len);

            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
            printf("Response sent to %s: %s\n", client_ip, buffer);
        }
    }

    close(server_fd);
    return 0;
}