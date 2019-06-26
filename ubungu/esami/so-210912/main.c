#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080
#define bound(var, min, max) (var > min) ? ((var < max)? var : max) : min;	
int q;

void die(const char* msg);
int answer(int data);
void sig_handler(int signo);

int main(int argc, char** argv) {
	struct sockaddr_in sa;
	int sock, fd;
	struct sigaction act;
	
	act.sa_handler = sig_handler;
	act.sa_flags = 0;
	q = atoi(argv[1]);

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	sa.sin_family = AF_INET;
	sa.sin_port = ntohs(PORT);
	sa.sin_addr.s_addr = INADDR_ANY;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		die("sock()");
	if (bind(sock, (struct sockaddr*)&sa, sizeof sa) < 0)
		die("bind()");
	if (listen(sock, SOMAXCONN) < 0)
		die("listen()");

	while(1) {
		fd = accept(sock, NULL, NULL);
		if (fd < 0)
			if (errno != EINTR)
				break;
			else
				continue;
		switch(fork()) {
			case -1:
				die("fork()");
			case 0:
			{ 
				/* serve */
				int data;
				read(fd, &data, sizeof data);

				sigprocmask(SIG_BLOCK, &act.sa_mask, NULL);
				data = answer(data);
				write(fd, &data, sizeof data);
				close(fd);
				exit(EXIT_SUCCESS);
			}
			default:
				close(fd);
		}
		printf("Loop\n");
		
	}
	perror("accept()");
	return 0;
}

void sig_handler(int signo) {
	switch(signo) {
	case SIGUSR1:
		q += 1;
		break;
	case SIGUSR2:
		q -= 2;
		break;
	}
	q = bound(q, 0, 100);
	printf("Handed signal , q=%d\n", q);
}

void die(const char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int answer(int data){
	float res = data;
	if (data % 100 == 0)
		res *= data/100;
	return res + q;	
}
