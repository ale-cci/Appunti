# Corradi Alessandro - 284026
# Disclaimer: Over-Engeneered only for experimentation purposes

CC = c99
SRC = prog-x.c
OUT = ${SRC:.c=}
EX = prog-0 prog-1 prog-2
VERSION=3

default: ${OUT}
	echo ${EX} | xargs -n1 cp ${OUT}


utils.o:
	$(CC) -Wall -c utils.c -o utils.o

${OUT}: ${SRC} utils.o
	$(CC) -Wall ${FLAGS} ${SRC} utils.o -o ${OUT}

clean:
	rm -f ${EX} ${OUT} utils.o


dist:
	tar -cf optional-${VERSION}.tar ${SRC} Makefile utils.c utils.h
	tar -tf optional-${VERSION}.tar

.PHONY: default dist clean
