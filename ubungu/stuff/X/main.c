#include<errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>

void die(char* msg) {
    fprintf(stderr, msg);
    exit(EXIT_FAILURE);
}


int main(){
    Display *x;
    if (!(x = XOpenDisplay(NULL)))
        die("asdf");
}
