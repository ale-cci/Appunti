#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define check(cond, errmsg) if(!(cond)){perror(errmsg); exit(EXIT_FAILURE);}
#define require(cond) if(!(cond)){usage(stderr); exit(EXIT_FAILURE);}

#define NAME_BYTES 32
#define AGE_BYTES 2
char* bkpFileName=".backup";

struct Person{
    char name[NAME_BYTES];
    char age[AGE_BYTES];

    struct Person* next;
    struct Person* prev;
};

void usage(FILE* f) {
    fprintf(f, "Usage: ...\n");
}

void printPerson(struct Person* person) {}

int readPerson(int fd, struct Person* person) {
    check(
        read(fd, &person->name, NAME_BYTES) == NAME_BYTES,
        "Error while reading name: "
    );
    person->name[NAME_BYTES-1] = 0;

    // Skipping empty space
    lseek(fd, 1, SEEK_CUR);

    check(
        read(fd, &person->age, AGE_BYTES) == AGE_BYTES,
        "Error while reading age: "
    );
    person->age[AGE_BYTES-1] = 0;

    person->next=NULL;
    person->prev=NULL;
    char tmp;
    return read(fd, &tmp, 1) == 1;
}


int main(int argc, const char** argv) {
    int fd;
    char* fContent;
    struct Person *personList,
                *ptrToLast;

    check((fd=open(bkpFileName, O_RDONLY)) >= 0, "Error opening file descriptor");


    personList = malloc(sizeof(struct Person));
    ptrToLast = personList;
    while (readPerson(fd, ptrToLast)){
        ptrToLast->next = malloc(sizeof(struct Person));
        ptrToLast->next->prev = ptrToLast;
        ptrToLast = ptrToLast->next;
    }

    // Deallocate person list


    close(fd);
    return 0;
}
