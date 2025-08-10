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
    struct sockaddr_in serv_addr;
    int serv_addr_len = sizeof(serv_addr);
    char buffer[MAX_BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    // {
    //     printf("\nConnection Failed \n");
    //     return -1;
    // }

    char *msg = "Requesting time";

    sendto(sock, (void *)msg, sizeof(msg), 0, (struct sockaddr *)&serv_addr, serv_addr_len);
    if (recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_addr, &serv_addr_len) < 0)
    {
        perror("recvfrom() failed");
        exit(1);
    }
    printf("Server message: %s", buffer);

    close(sock);

    return 0;
}