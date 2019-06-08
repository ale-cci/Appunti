#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


typedef struct _RICHIESTA_MDG {
    int req;
} RICHIESTA_MSG;


typedef struct _RISPOSTA_MSG {
    int answ;
} RISPOSTA_MSG;

int main(int argc, char* argv[]) {
    int sock, length, portno;
    struct sockaddr_in server, client;
    int pid, s, msgsock, rval, rval2, i;
    struct hostent *hp, *gethostbyname();

    RICHIESTA_MSG request;
    RISPOSTA_MSG answer;


    if (argc != 2) {
        printf("Usage? %s <port_number>\n", argv[0]);
        exit(EINVAL);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    portno = atoi(argv[1]);

    server.sin_family = AF_INET;

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);

    if (bind(sock, (struct sockaddr*)& server, sizeof(server)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    printf("Socket port #%d\n", ntohs(server.sin_port));

    listen(sock, 2);

    while(1) {
        if ((msgsock = accept(sock, (struct sockaddr*)&client, (socklen_t*)&length)) < 0) {
            perror("accept");
        } else {
            printf("Connection from %s, port %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));


            if ((pid = fork()) < 0) {
                close(sock);
                read(msgsock, &request, sizeof(request));

                answer.answ = request.req + (rand() % 100);
                write(msgsock, &answer, sizeof(answer));
                close(msgsock);
                exit(0);
            } else {
                if (pid == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                close(msgsock);
            }
        }
    }
    exit(0);
}

