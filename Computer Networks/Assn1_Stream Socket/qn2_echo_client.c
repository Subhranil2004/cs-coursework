#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main()
{
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Replace "127.0.0.1" with the server's IP address if running on separate machines
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
    {
        perror("Invalid address/Address not supported");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to the echo server.\n");
    printf("Enter a message (type 'exit' to quit):\n");

    while (1)
    {
        // Get user input
        printf("> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        if (strcmp(buffer, "exit") == 0)
        {
            write(client_fd, buffer, strlen(buffer) + 1); // send(client_fd, buffer, strlen(buffer), 0); // Notify the server to close
            printf("Exiting...\n");
            break;
        }

        // Send message to the server
        write(client_fd, buffer, strlen(buffer) + 1); // send(client_fd, buffer, strlen(buffer), 0);

        // Receive the echoed message from the server
        int bytes_received = read(client_fd, buffer, BUFFER_SIZE); // recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0)
        {
            perror("Receive failed");
            break;
        }

        buffer[bytes_received] = '\0'; // Null-terminate the string
        printf("Server response: %s\n", buffer);
    }

    close(client_fd);
    return 0;
}