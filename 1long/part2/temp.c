#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char const *argv[],char **envp)
{
    /* code */
    char **env;
    for(env = envp; *env != 0; env++)
    {
        char *thisEnv = *env;
        printf("%s\n", thisEnv);
        
    }
    chdir(getenv("HOME"));
    for(env = envp; *env != 0; env++)
    {
        char *thisEnv = *env;
        printf("%s\n", thisEnv);
        
    }
    return 0;
}
