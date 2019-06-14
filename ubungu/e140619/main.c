/* Nome Cognome - Matricola */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define PASSWORD "so-1819"
#define LOCK sigprocmask(SIG_BLOCK, /* current signals */ )
#define UNLOCK sigprocmask(SIG_UNBLOCK,  /* ols_sigmask */, /*proc_mask */)
/* Number of processses */
int N;
int active_conn = 0;

/* User Accounts */
int accounts[10];
int child_count =0;
int children[1024];

void init(sigmask);
void die(const char* msg);
int open_socket(int portno);

void client_process(int client_fd);

int main(int argc, char* argv[]) {
	int sock, cfd;
	char buffer[128];
	struct sockaddr_in cli;
	socklen_t clen = sizeof cli;

	for (int i=0; i < N; ++i)
		accounts[i] = 0;
	ppid = getpid();

	assert(argc == 2);
	N = atoi(argc[2]);
	assert(3 <= N && N <= 10);

	sock = open_socket(PORT);
		
	
	while(1) {
		cfd = accept(sock, (struct sockaddr*) &cli, &clen);	
		Log(INFO, "Incoming connection from client with ip %d\n", inet_nota(cli.sin_addr));
		if (cfd > 0 && children[child_count] = fork()) {
		
			dprintf(cfd, "Password: ");
			memset(buffer, 0, sizeof buffer);
			read(cfd, buffer, sizeof buffer);

			tmp = strtok(buffer, "\n");
			if ((strcmp(tmp, "so-1819") == 0) {
				/* Authentication Successful */
				client_process(cfd);
			} else 
				dprintf(cfd, "Authentication failed!\n");

			close(cfd);
			exit(0);
		}

		else if (cfd < 0)
			perror("accept()");
		else  
			close(cfd);
		
	}
	
	return EXIT_FAILURE;	
}


int open_socket(int portno) {
	struct sockaddr_in sa;
	int sock;

	sa.sin_family = AF_INET;
	sa.sin_port = ntohs(portno);
	sa.sin_addr.s_addr = INADDR_ANY;

	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		die("socket()");
	
	if (bind(sock, &sa, sizeof sa) < 0)
		die("bind()");
	
	if (listen(sock, SOMAXCONN) < 0) 
		die("listen()");

	return sock;
}


void die(const char*msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void sig_handler(int signo) {
	// Disable sigprocmask
	switch(signo) {
		case SIGUSR1;
			log_level = CRITICAL;
			break;
		case SIGCHLD:
			// wait child pid and shift table
			read(piped[1], accounts, sizeof accounts);	
			// update all child account table
			break;
	}
	// Reenable sigprocmask
}

void  init_signals() {
	signal(SIGUSR1, sig_handler);
	signal(SIGCHLD, sig_handler);
}


void client_process(int client_fd){
	int target, amount;
	char buffer[128];
	char *tmp;
	

	dprintf("Choose an option: \n"
			" - CHARGE <USER> <AMOUNT>\n"
			" - INFO <USER>\n"
			" - WITHDRAW <USER> <AMOUNT>\n"
			"\m>");
	read(client_fdd, buffer, sizeof buffer);

	tmp = strtok(buffer, " ");
	if (strcmp(tmp, "CHARGE") == 0) {
		tmp = strtok(NULL, " ");
		target = atoi(tmp);
		tmp = strtok(NULL, "\n");
		amount = atoi(tmp);

		account[target] += amount;
		dprintf("Client %d : %d$\n" target, amount[target]);
	}
	else if (strcmp(tmp, "INFO") == 0) {
		tmp = strtok(NULL, "\n");
		target = atoi(tmp);
		dprintf("Client %d : %d$\n" target, amount[target]);
	} else if (strcmp(tmp, "WITHDRDRAW") == 0) {
		tmp = strtok(NULL, " ");
		target = atoi(tmp);
		tmp = strtok(NULL, "\n");
		amount = atoi(tmp);

		if (account[target] >= amount) {
			account[target] -= amount;
			dprintf(client_fd, "Withdrawed %d$ from User %d\n", amount, account[target]);
		}
		else {
			dprintf(client_fd, "Client %d has not enough money!\n");
		}
		dprintf(client_fd, "Client %d : %d$\n" target, amount[target]);
	} else {
		dprintf(client_fd, "Unrecognized command <%s>\n", tmp);
	}
}

