#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in serv_addr, client_addr;
    int serv_addr_len = sizeof(serv_addr);
    int client_addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE] = {0};
    time_t now;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&serv_addr, serv_addr_len) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // if (listen(server_fd, 3) < 0)
    // {
    //     perror("listen");
    //     exit(EXIT_FAILURE);
    // }

    // if ((new_socket = accept(server_fd, (struct sockaddr *)&serv_addr, (socklen_t *)&serv_addr_len)) < 0)
    // {
    //     perror("accept");
    //     exit(EXIT_FAILURE);
    // }
    printf("Server running on port: %d", PORT);
    while (1)
    {
        recvfrom(server_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_len);
        time(&now);
        snprintf(buffer, MAX_BUFFER_SIZE, "%.24s\r\n", ctime(&now));
        sendto(server_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, client_addr_len);
        sleep(1); // Send time every second
    }
    close(server_fd);

    return 0;
}