#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#define LEN(array) (sizeof array / sizeof array[0])

/* Possible log levels */
enum {DEBUG, INFO, CRITICAL};

/* Available services */
enum {SERVICE_SUM, SERVICE_PROD};


struct Response {
	int fd;
	int service;
	struct sockaddr client;
	socklen_t csize;
};

int log_level = DEBUG;

void die(const char* msg);
void init();
void loglevel(int signo);
void Log(int level, const char* fmt, ...); 

int new_sockstream(int port);
int accept_any(int sock_list[], int nof_socks, struct Response* resp);


int main(int argc, const char* argv[]) {
	int sock;
	struct sockaddr_in sa;
	struct sockaddr client;
	struct Response resp;

	/* Services sockets */
	int sock_list[2];

	socklen_t clen;
	sigset_t sigmask;

	Log(INFO, "Initializing Server...\n");
	init(&sigmask);

	// Initializing sockets
	sock_list[SERVICE_PROD] = new_sockstream(8000);
	sock_list[SERVICE_SUM] = new_sockstream(8080);
	Log(DEBUG, "Socket initizlied...\n");

	// Accept
	sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
	Log(DEBUG, "Ready, listening for incoming connections...\n");

	while(1) {
		if (accept_any(sock_list, LEN(sock_list), &resp) < 0) {
			if (errno == 0) {
				Log(INFO, "Timeout!\n");
				exit(EXIT_SUCCESS);
			}
			perror("accept_any()");
			continue;
		}

		if (resp.fd > 0 && fork() == 0) {
			char op1[3],
			op2[3];
			int msg1, msg2;

			Log(INFO, "Slave process answering to client...\n");

			read(resp.fd, op1, sizeof op1);
			read(resp.fd, op2, sizeof op2);

			msg1 = atoi(op1);
			msg2 = atoi(op2);

			Log(DEBUG, "Received from child %d and %d\n", msg1, msg2);

			/* Writing response based on the service type */
			switch(resp.service) {
				case SERVICE_SUM:
					dprintf(resp.fd, "%d", msg1 + msg2);
					break;
				case SERVICE_PROD:
					dprintf(resp.fd, "%d", msg1 * msg2);
					break;
			}
			close(resp.fd);
			exit(0);
		}
		close(resp.fd);
	}    


	return 0;
}

void die(const char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void loglevel(int signo) {
	Log(INFO, "Switching log level...\n");
	switch(signo) {
		case SIGUSR1:
			log_level = DEBUG;
			break;
		case SIGUSR2:
			log_level = CRITICAL;
			break;
	}
}


void init(sigset_t* sigmask) {
	/* Initializing handled signals */
	sigemptyset(sigmask);

	sigaddset(sigmask, SIGUSR1);
	sigaddset(sigmask, SIGUSR2);

	sigprocmask(SIG_BLOCK, sigmask, NULL);

	signal(SIGUSR1, loglevel);
	signal(SIGUSR2, loglevel);
}

void Log(int level, const char* fmt, ...){
	if (level < log_level)
		return;

	va_list vl;
	va_start(vl, fmt);
	vprintf(fmt, vl);
}

int new_sockstream(int port) {
	int sock;
	struct sockaddr_in sa;  

	/* Init sockaddr structure */
	sa.sin_family      = AF_INET;
	sa.sin_port        = ntohs(port);
	sa.sin_addr.s_addr = INADDR_ANY;

	/* Opening socket connection to @port */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		die("socket()");

	/* Bind socket to sockaddr */
	if (bind(sock, (struct sockaddr*)&sa, sizeof sa) < 0)
		die("bind()");

	/* Start listening incoming connections */
	listen(sock, SOMAXCONN);
	return sock;
}

int accept_any(int sock_list[], int nof_socks, struct Response* resp) {
	fd_set filedes;
	int maxfd =-1,
		i, rv, fd;
	/* Response timeout 1m */
	struct timeval timeout = {60, 0};

	/* Initializing fd set */
	FD_ZERO(&filedes);

	for(i=0; i<nof_socks; ++i) {
		FD_SET(sock_list[i], &filedes);
		if (sock_list[i] > maxfd)
			maxfd = sock_list[i];
	}

	rv = select(maxfd +1, &filedes, 0, 0, &timeout);
	if (rv < 0)
		return -1;

	/* Deteing corresponding fd */
	for (i = 0; i < nof_socks; ++i) {
		if (FD_ISSET(sock_list[i], &filedes)) {
			resp->service = i;
			resp->fd = accept(sock_list[i], &resp->client, &resp->csize);
			return EXIT_SUCCESS;
		}
	}

	return -1;
}
