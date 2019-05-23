#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
    char s[100];
    size_t sl;

    strcpy(s, "Questa stringa andra’ sullo standard output\n");
    sl = strlen(s);
    if ((write(1, s, sl)) == -1)
        perror("write error");
    return 0;
}
