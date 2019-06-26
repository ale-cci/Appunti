#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

enum{P1, P2, Pr};

/* Forward mode, used in Pr to determine message receiver */
enum{FWD_ANY, FWD_P2};
int fwd_mode = FWD_ANY;

/* Pipe between processes r-1 & r-2 */
int PP[3][2];

/* Spawn Pr, P1, P2   
 * Returns: pid of Pr 
 */
int spawn_proc();

/* Basic Message Structure */
struct Msg {
	int to;
	int data;
} msg;

int *pid_tbl;

void pmessage(const char* m);
void sig_handler(int signo);

void die(const char* msg);

int main(int argc, char**argv) {
	srand(time(NULL));
	assert(argc == 2);
	int N = atoi(argv[1]);
	if (pipe(PP[Pr]) < 0)
		die("pipe PP_PR:");

	// pid_tbl = mmap(0, sizeof(int)* 3, 
	pid_tbl = malloc(sizeof(int)*3);
	spawn_proc();

	while(1) {
		sleep(1);
		msg.to = rand() % 2;
		msg.data = rand() % N;

		printf("\n");
		pmessage("Father");	
		write(PP[Pr][1], &msg, sizeof(msg));
		kill(pid_tbl[Pr], SIGALRM);
	}
}

int spawn_proc(){ 

	if (pipe(PP[P1]) < 0)
		die("pipe1()");
	if (pipe(PP[P2]) < 0)
		die("pipe2()");

	if ((pid_tbl[P1] = fork()) == 0){
		// P1 Code
		while(1) {
			if (read(PP[P1][0], &msg, sizeof msg) > 0)
				pmessage("P1");
		}
		exit(0);
	}

	if ((pid_tbl[P2] = fork()) == 0){
		// P2 Code
		while(1) {
			if (read(PP[P2][0], &msg, sizeof msg) > 0)
				pmessage("P2");
		}
		exit(0);
	}
	
	if ((pid_tbl[Pr] = fork()) == 0){
		// Pr Code
		printf("Initialized Pr with PID: %d\n", getpid());
		// Signal Handler
		struct sigaction act;
		act.sa_handler = sig_handler;
		act.sa_flags   = 0;
		sigemptyset(&act.sa_mask);

		sigaddset(&act.sa_mask, SIGUSR1);
		sigaddset(&act.sa_mask, SIGUSR2);
		sigaddset(&act.sa_mask, SIGALRM);

		sigaction(SIGUSR2, &act, NULL);
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGALRM, &act, NULL);
		while(1)
			sleep(10);

		exit(0);
	}

	return pid_tbl[Pr];
}

void sig_handler(int signo) {
	switch(signo) {
	case SIGALRM:
		// Forward Message;
		if (read(PP[Pr][0], &msg, sizeof msg) < 0)
			die("read()");
		// Switch dest
		pmessage("Pr");	

		switch(fwd_mode) {
		case FWD_P2: 
			write(PP[P2][1], &msg, sizeof msg);
			break;
		case FWD_ANY:
		default:
			write(PP[msg.to][1], &msg, sizeof msg);
		}
		break;

	case SIGUSR1:
		// Inoltrare a P2 messaggi destinati a P1
		printf("Forawrding Messages to P2\n");
		fwd_mode = FWD_P2;
		break;

	case SIGUSR2:
		// Reset destinazione messaggi
		printf("Reset Message Forwarding\n");
		fwd_mode = FWD_ANY;
		break;
	}
}

void pmessage(const char* m) {
	printf("<%s, TO: %d, DATA: %d>\n", m, msg.to, msg.data);
}

void die(const char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}
