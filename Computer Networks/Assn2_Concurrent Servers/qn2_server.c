#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
// #include <sys/wait.h>
// #include <unistd.h>
#include <pthread.h>
// // for windows
// #include <winsock2.h>  // for windows
// typedef int socklen_t; // define socklen_t for Windows
// //
#include <ctype.h>
#include <time.h>
#include <signal.h>
#define PORT 12345
#define BUFFER_SIZE 20

char behaviour[5];
char buffer[BUFFER_SIZE];

void *client_func(void *fd)
{
    int *client_fd = (int *)fd;
    printf("Sent %s\n", behaviour);
    // Send the modified buffer back to the client
    write(*client_fd, buffer, strlen(buffer) + 1);
    close(*client_fd);
}

int main()
{
    signal(SIGCHLD, SIG_IGN);
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
        printf("Connection established. Client IP: %s | ", client_ip);

        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, client_func, (void *)(&client_fd)) != 0)
        {
            perror("Thread creation failed");
            close(client_fd);
        }
        pthread_detach(client_thread);
    }

    return 0;
}