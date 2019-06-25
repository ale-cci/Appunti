#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <assert.h>
#include <netinet/ip.h>
#include <signal.h>

#define PORT 8080
#define LEN(array) (sizeof(array) / sizeof(array[10]))

int q;

void die(const char* msg);
void init(sigset_t* set);
void sighandler(int signo);

int main(int argc, const char* argv[]) {
	int sock, cfd;
	struct sockaddr_in sa;
	struct sockaddr client;
	socklen_t clen;
	sigset_t sigset;

	sa.sin_family = AF_INET;
	sa.sin_port   = htons(PORT);
	sa.sin_addr.s_addr = INADDR_ANY;

	printf("Initializing server...\n");
	init(&sigset);
	sock = socket(AF_INET, SOCK_STREAM, 0);

	assert(argc == 2);
	q = atoi(argv[1]);

	if (sock < 0)
		die("sock()");

	if (bind(sock, (struct sockaddr*) &sa, sizeof sa) < 0)
		die("sockaddr()");

	if (listen(sock , SOMAXCONN) < 0)
		die("listen()");

	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	printf("Server running on port %d\n", PORT);

	while(1) {
		cfd = accept(sock, &client, &clen);
		if (cfd < 0) {
			perror("accept()");
			continue;
		}
		if (fork() == 0) {
			/* Read client data */
			char client_msg[8];
			int data;
			float M = 1.;


			if (read(cfd, client_msg, LEN(client_msg)) < 0)
				die("read()");

			data = atoi(client_msg);

			if (!(data % 100))
				M = 0.01;
			printf("Received client message %s\n", client_msg);

			dprintf(cfd, "%f\n", M*data+ q);

			close(cfd);
			exit(0);
		}

		close(cfd);
	}


	return EXIT_SUCCESS;
}

void init(sigset_t* mask) {
	sigemptyset(mask);
	sigaddset(mask, SIGUSR1);
	sigaddset(mask, SIGUSR2);

	sigprocmask(SIG_BLOCK, mask, NULL);
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);

}

void sighandler(int signo) {
	printf("Changin q...\n");
	switch(signo){
	case SIGUSR1:
		q += 1;
		break;
	case SIGUSR2:
		q -= 1;
		break;
	}

	/* Bounding q in range 0..100 */
	q = (q < 0)? 0: q;
	q = (q > 100)? 100: q;
}

void die(const char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}
