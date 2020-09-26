#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ls.h"
#include"cd.h"
#include<sys/wait.h> 
#include <unistd.h>
#include <sys/types.h> 

void driver(char s[])
{
    if(s!=NULL)
        {
            switch (s[0])
            {
            case 'c':
                if(strcmp(s,"cd")==0)
                {
                    cd();
                }
                break;   
            case 'e':
                if(strcmp(s,"exit")==0)
                {
                    printf("exiting now.... \n");
                    exit(0);
                }
                break;
            case 'l':
                if(strcmp(s,"ls")==0)
                {
                    int id=fork();
                    if(id==0)
                    {
                        ls();
                        exit(0);
                    }
                    else
                    {
                        int stat=0;
                        waitpid(id,NULL,0);
                    }
                }
                break;
            default:
                break;
            }
        }

}

int main(int argc, char const *argv[])
{
    /* code */
    while(1)
    {
        char s[100];
        printf("boomerOp>>");
        scanf("%s",s); 
        driver(s);       

    }
    return 0;
}
