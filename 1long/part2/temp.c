#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    /* code */
    printf("hello\n");
    int x=fork();
    printf("waup\n");
    return 0;
}
