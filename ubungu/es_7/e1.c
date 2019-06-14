#include <arpa/inet.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include <sys/select.h>
#define LEN(x) sizeof(x) / sizeof(x[0])

enum {CLOCK, DNS};

struct Response {
    int fd;
    int service;
    struct sockaddr_in sa;
};

int sock_init(int port);

int accept_any(int sock_fds[], int fds_len, struct Response* rt);

int main(int argc, char* argv[]) {
    int accept_status;
    struct Response req;

    char msg[128],
         hostname[32] = "localhost";
    int sock_list[2];
    int fds[2];

    sock_list[CLOCK] = sock_init(8080);
    sock_list[DNS] = sock_init(8000);

    while(1) {
        accept_status = accept_any(
            sock_list,
            sizeof sock_list / sizeof sock_list[0],
            &req);

        if (accept_status == -2) {
            printf("Timeout!\n");
            exit(0);
        }
        if (accept_status == -1) {
            perror("accept_any()");
            continue;
        }

        if (fork() == 0) {

            printf("Responding to client with service %d\n", req.service);
            switch (req.service) {
            case CLOCK:
                sprintf(msg, "Request received from %s, on port %d\n\0", inet_ntoa(req.sa.sin_addr), ntohs(req.sa.sin_port));

                {
                    time_t curtime = time(NULL);
                    char* stime = ctime(&curtime);
                    strcpy(msg, stime);
                }

                break;
            case DNS:
                /* dns service */

                memset(hostname, 0, LEN(hostname));

                read(req.fd, hostname, sizeof hostname / sizeof hostname[0]);

                /* NOTE: Vulnerable to script injection */
                sprintf(msg, "nslookup %s", hostname);

                pipe(fds);
                dup2(fds[1], fileno(stdout));
                system(msg);

                /* Read system command output */
                memset(msg, 0, LEN(msg));
                read(fds[0], msg, sizeof msg);

                close(fds[0]);
                break;
            default:
                printf("Unrecognized service %d\n", req.service);
            }

            write(req.fd, msg, strlen(msg));
            close(req.fd);
            exit(0);
        }
        close(req.fd);
    }
    return 0;
}


int sock_init(int port) {
    /* Bind socket to localhost:port */
    struct sockaddr_in sa;
    int sock;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(port);

    /* Init socket */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    if (bind(sock, (struct sockaddr*)&sa, sizeof sa) < 0) {
        perror("bind()");
        exit(EXIT_FAILURE);
    }

    listen(sock, 3);
    return sock;
}

int accept_any(int sock_fds[], int fds_len, struct Response* rt) {
    int i, rv, max_fd = -1;
    int addr_len = sizeof rt->sa;
    fd_set fds;
    FD_ZERO(&fds);

    /* 5m of timeout */
    struct timeval tv = {5*60, 0};

    for ( i=0; i< fds_len; ++i) {
        FD_SET(sock_fds[i], &fds);
        if (sock_fds[i] > max_fd)
            max_fd = sock_fds[i];
    }

    rv =  select(max_fd+1, &fds, NULL, NULL, &tv);
    if (rv < 0)
        return -1;

    rv = 0;
    for (i = 0; i < fds_len; ++i)
        if (FD_ISSET(sock_fds[i], &fds)) {
            rt->fd = accept(sock_fds[i], (struct sockaddr*)&rt->sa, &addr_len);
            rt->service = i;
            return EXIT_SUCCESS;
        }
    /* Timeout */
    return -2;
}

