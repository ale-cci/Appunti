#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define CHILD_PROCESSES 2

void run_child(int child_id) {
    printf("\n\nChild: %d"
            "\nPid: %d", child_id, getpid());
}

void keyboard_interrupt_handler(int signal) {
    printf("\nGotcha!");
}

int main(int argc, const char ** argv) {
    int current_child,
        child_ecode,
        child_pid;

    for (current_child=1; current_child <= CHILD_PROCESSES; ++current_child){
        child_pid = fork();

        if (child_pid < 0) {
            perror("Fork error: ");
            exit(1);
        } else if (child_pid == 0) {
            run_child(current_child);
            exit(0);
        }
    }



    printf("Running main process with pid %d", getpid());

    // for (current_child=1; current_child <= CHILD_PROCESSES; ++current_child) {
    //     child_pid = wait(&child_ecode);
    //     printf("Child with pid %d exited with code %d\n", child_pid, child_ecode);
    // }

    signal(SIGINT, keyboard_interrupt_handler);

    for(;;) {
        printf("\nStill running");


        usleep(300000);
    }
    return 0;
}
