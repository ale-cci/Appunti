#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    int pdchf[2], pdfch1[2], pdfch2[2];
    int pid1, pid2;

    struct msg {
        int mpid;
        int n;
    } m1, m2;

    int n1, n2;

    if (pipe(pdchf) < 0)
        die("pipe");

    if (pipe(pdfch1) < 0)
        die("pipe pdfch1");

    if (pipe(pdfch2) < 0)
        die("pipe pdfch2");

    if ((pid1 = fork()) < 0)
        die("fork");
    else if (pid1 == 0) {
        close(pdchf[0]);
        close(pdfch1[1]);

        close(pdfch2[0]);
        close(pdfch2[1]);

        m1.mpid = getpid();
        m1.n = atoi(argv[1]);

        write(pdchf[1], &m1, sizeof(m1));
        printf("figlio 1: ho scritto al padre %d\n", m1.n);
        read(pdfch1[0], &m1, sizeof(m1));
        printf("figlio 1: il padre mi ha scritto %d\n", m1.n);
        exit(0);
    } else {
        if ((pid2 = fork()) < 0)
            exit(2);
        else if (pid2 == 0) {
            close(pdchf[0]);
            close(pdfch2[1]);
            close(pdfch1[0]);
            close(pdfch1[1]);

            m2.mpid = getpid();
            m2.n = atoi(argv[2]);

            /* Comunica al padre il proprio messaggio */
            write(pdchf[1], &m2, sizeof(m2));
            printf("figlio 2: ho scritto al padre %d\n", m2.n);

            /* Legge il messaggio del padre */
            read(pdfch2[0], &m2, sizeof(m2));
            printf("figlio 2: il padre mi ha scritto  %d\n", m2.n);
        } else {
            /* father process */
            close(pdchf[1]);
            close(pdfch1[0]);
            close(pdfch2[0]);

            read(pdchf[0], &m1, sizeof(m1));
            read(pdchf[0], &m2, sizeof(m2));

            srand(time(0));

            n1 = 1+(int) (m1.n * (rand()/ (RAND_MAX+1.0)));
            n2 = 1+(int) (m2.n * (rand()/ (RAND_MAX+1.0)));

            if (m1.mpid == pid1) {
                m1.n = n1;
                m2.n = n2;
                write(pdfch1[1], &m1, sizeof(m1));
                write(pdfch2[1], &m2, sizeof(m2));
            } else {
                m1.n = n2;
                m2.n = n1;
                write(pdfch1[1], &m2, sizeof(m2));
                write(pdfch2[1], &m1, sizeof(m1));
            }
            sleep(1);
            exit(0);
        }
    }
}

