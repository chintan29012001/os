#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"cd.h"
#include<sys/wait.h> 
#include <unistd.h>
#include <sys/types.h> 
void split(char s[],char*args[])
{
    // printf("abs");
    int i=0;
    int j=0;
    int k=0;
    args[j]=(char*)malloc(3);
    for(;i<s[i]!='\0';i++)
    {
        if(s[i]==' ')
        {
            j++;
            k=0;
            args[j]=(char*)malloc(3*sizeof(char));
        }
        else
        {
            args[j][k]=s[i];
            k++;
        }

    }
    j++;
    args[j]=NULL;
    j++;
    // for(int i=0;args[i]!=NULL;i++)
    // {
    //     printf("%d \n",i);

    // }
    // for(int i=0;args[i]!=NULL;i++)
    // {
    //     printf("%s \n",args[i]);

    // }

}


void drivers(char* args[])
{
    if(args[0]!=NULL)
        {
            // char args[10][3];
            
            // printf("in parent prog\n");
            // printf("%s\n",args[0]);
            switch (args[0][0])
            {
            case 'c':
                if(strcmp(args[0],"cd")==0)
                {
                    cd();
                }
                break;   
            case 'e':
                if(strcmp(args[0],"exit")==0)
                {
                    printf("exiting now.... \n");
                    for(int i=0;args[i]!=NULL;i++)
                    {
                        free(args[i]);

                    }
                    exit(0);
                }
                break;
            case 'l':
                if(strcmp(args[0],"ls")==0)
                {
                    
                    int id=fork();
                    if(id==0)
                    {
                        printf("in child process");
                        execv("./ls",args);
                        // printf("end of child process \n");
                        exit(0);
                    }
                    else
                    {
                        int stat=0;
                        waitpid(id,NULL,0);
                        // printf("child process exited\n");
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
        scanf("%[^\n]%*c",s); 
        char* args[10];
        split(s,args);
        drivers(args);       

    }
    return 0;
}

