#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#define check(cond, errmsg) if(!(cond)){fflush(stdout); perror(errmsg); exit(EXIT_FAILURE);}
#define require(cond) if(!(cond)){usage(stderr); exit(EXIT_FAILURE);}

#define NAME_BYTES 5
#define AGE_BYTES 4

struct Person {
    char name[NAME_BYTES];
    char age[AGE_BYTES];
}* personList;

int printPerson(struct Person* person);
void readPerson(int fd, struct Person* person);
int stoi(const char* str);
void usage(FILE* stream);

int main(int argc, const char** argv) {
    int length, fd, id, i;
    char sLength[4];

    require(argc == 2);

    fd = open("list.txt", O_RDONLY);
    check(fd >= 0, "Error opening file:");
    check( read(fd, sLength, sizeof(sLength)) == sizeof(sLength), "Read Error");

    length = stoi(sLength);
    lseek(fd, 1, SEEK_CUR);


    printf("\nFound %d persons", length);
    personList = malloc(sizeof(struct Person)*length);

    for (i=0; i<length; ++i) {
        readPerson(fd, &personList[i]);
    }

    id=stoi(argv[1]);
    assert(0 <= id && id < length && "\nIndex out of range");

    printf("\nPrinting data of Person %d", id);
    printPerson(&personList[id]);

    return EXIT_SUCCESS;
}



int printPerson(struct Person* person) {
    return printf("\nName: %s"
                  "\nAge: %s", person->name, person->age);
}

void readPerson(int fd, struct Person* person) {
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
}

int stoi(const char* str) {
    int num = 0, i,
        offset=0,
        sign=1;

    while(!isdigit(str[offset])) {
        if (str[offset] == '-')
            sign *= -1;
        ++offset;
    }

    for (i=offset; isdigit(str[i]); ++i) {
        num *= 10;
        num += str[i] - '0';
    }
    return  num*sign;
}

void usage(FILE* stream){
    fprintf(stream, "Usage . <person_id>");
}
