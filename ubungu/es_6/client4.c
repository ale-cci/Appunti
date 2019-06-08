#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char* argv[]) {
    int sock, port;
    char msg[26];
    struct sockaddr_in client;
    size_t len = sizeof client;
    struct hostent *hp;

    if (argc != 2) {
        printf("Usage: %s <port_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    port = atoi(argv[1]);
    hp = (struct hostent*) gethostbyname("127.0.0.1");


    client.sin_family = AF_INET;
    memcpy(&client.sin_addr, hp->h_addr_list[0], hp->h_length);
    client.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*)&client, len) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    read(sock, msg, sizeof msg);
    printf("Received '%s' from server\n", msg);

    exit(0);
}
