#include <stdio.h>
#include <unistd.h>

int main()
{
    if ((unlink("test2.dat")) == -1)
    {
        perror("unlink error");
        return 1;
    }
    return 0;
}
