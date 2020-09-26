#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h>
//cd

void cd()
{
    chdir(getenv("HOME"));
    // printf("%s",getenv("HOME"));

}