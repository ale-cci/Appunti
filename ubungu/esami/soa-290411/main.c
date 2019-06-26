#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/ip.h>
#include <unistd.h>

#define PORT 8080

void die(const char* msg);
void server(int sock, struct sockaddr_in* specs);
void client(int sock);

int main(int argc, char** argv) {
	struct sockaddr_in srv;
	int sock;

	srv.sin_family = AF_INET;
	srv.sin_port = ntohs(PORT);
	srv.sin_addr.s_addr = INADDR_ANY;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		die("sock()");


	/* srv structure not used anymore, it's fine to pass it here */
	if (connect(sock, (struct sockaddr*)&srv, sizeof srv) < 0) {
		if (errno == ECONNREFUSED ) {
			server(sock, &srv);	
			exit(EXIT_SUCCESS);
		} else 
			exit(EXIT_FAILURE);
	}
	client(sock);
	exit(EXIT_SUCCESS);
}


void die(const char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void server(int sock, struct sockaddr_in* specs) {
	int client_fd, msg;
	printf("Initilizing Server...\n");	

	if (bind(sock, (struct sockaddr*)specs, sizeof (struct sockaddr_in) ) < 0)
		die("bind()");
	if (listen(sock, SOMAXCONN) < 0)
		die("listen()");

	if ((client_fd = accept(sock, NULL, NULL)) < 0) 
		die("accept()");

	read(client_fd, &msg, sizeof msg);
	printf("pow(%d, 2) = %d\n", msg, msg*msg);
	printf("Bye!\n");
	close(sock);
}

void client(int conn) {
	srand(getpid());
	int random = rand() % 10;

	printf("Initilizing Client...\n");	
	printf("Sending to Main server %d...\n", random);
	write(conn, &random, sizeof random);

	printf("Bye!\n");
	close(conn);
}
