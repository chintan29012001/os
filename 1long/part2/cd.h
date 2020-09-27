#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
//cd

void cd()
{
    chdir(getenv("HOME"));
    // printf("%s",getenv("HOME"));
}
void cd1(char path[])
{
    if(path==NULL)
        return;
    struct stat s;
    int err=stat(path,&s);
    if(err==0&& S_ISDIR(s.st_mode))
    {
        printf("exists\n");
    }
    else 
    {
        printf("does not exit");
    }
}