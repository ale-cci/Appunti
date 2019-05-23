#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

#define N 4096

int main()
{
    char buffer[N];
    int nread;

    nread = read(0, buffer, N);
    for( int i=0; i<N; ++i)
        buffer[i] = tolower(buffer[i]);
    if (nread == -1)
        perror("read error");

    if ((write(1, buffer, nread)) != nread)
        perror("write error");

    return 0;
}
