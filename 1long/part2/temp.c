#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    /* code */
    printf("hello\n");
    int x=fork();
    printf("wassup\n");
    return 0;
}
