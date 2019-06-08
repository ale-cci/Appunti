#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>

int sock;

void quit(int signo) {
    printf("Socket connection closed\n");
    close(sock);
    exit(0);
}

int main(int argc, char* argv[]) {
    char buf[26];
    time_t ticks;
    int length, msgsock, rval, portno;
    struct sockaddr_in server;

    if (argc != 2) {
        printf("Usage: %s <port_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, quit);

    printf("\n*-------------------------------------------------------------------------------*\n"
             "*                                                                               *\n"
             "*                      SERVER data e ora concorrenti                            *\n"
             "*                                                                               *\n"
             "*               ^c per terminare l'esecuzione                                   *\n"
             "*                                                                               *\n"
             "*-------------------------------------------------------------------------------*\n\n");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    portno = atoi(argv[1]);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);

    if (bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    length = sizeof server;

    if (getsockname(sock, (struct sockaddr*)&server, &length) < 0) {
        perror("getsockname");
        exit(EXIT_FAILURE);
    }

    printf("Socket port #%d\n\n", ntohs(server.sin_port));
    listen(sock, 2);
    while(1) {
        msgsock = accept(sock, (struct sockaddr*) NULL, (int*) NULL);
        if (msgsock == -1)
            perror("accept");
        else {
            ticks = time(NULL);
            strcpy(buf, ctime(&ticks));

            if ((rval = write(msgsock, buf, sizeof(buf))) < 0)
                perror("write");

            printf("%d byte scritti\n", sizeof(buf));
        }
        close(msgsock);
    }
    exit(0);
}


