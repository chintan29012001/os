#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    /* code */
    char string[]={"a.txt"};
    remove(string);
    return 0;
}
