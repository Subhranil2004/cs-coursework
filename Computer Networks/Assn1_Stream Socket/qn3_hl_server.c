#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
// // for windows
// #include <winsock2.h>  // for windows
// typedef int socklen_t; // define socklen_t for Windows
// //
#include <ctype.h>
#include <time.h>

#define PORT 12345
#define BUFFER_SIZE 20

int main()
{
    char *ID = "2022ITB012";
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT); // Convert to network byte order

    // Bind socket to the specified port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for (upto 5 simultaneous) incoming connections
    if (listen(server_fd, 5) == -1)
    {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Set server behaviour: HATER or LOVER.
    srand(time(NULL));
    int prob = rand() % (100 + 1);
    char behaviour[5];
    char buffer[BUFFER_SIZE];

    strcpy(behaviour, prob <= 80 ? "H" : "L");
    snprintf(buffer, BUFFER_SIZE, "%s:%s", ID, behaviour);
    printf("Server is running on port %d...\n", PORT);
    while (1)
    {
        // Accept a client connection
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd == -1)
        {
            perror("Accept failed");
            continue;
        }

        // Print client's IP address
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        printf("Connection established with client: %s\tSent %s\n", client_ip, behaviour);

        // Send the modified buffer back to the client
        write(client_fd, buffer, strlen(buffer) + 1); // send(client_fd, buffer, strlen(buffer), 0);

        // Close the connection with the client
        // close(client_fd);
    }

    close(server_fd);
    return 0;
}