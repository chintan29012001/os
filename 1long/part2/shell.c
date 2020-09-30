#include<sys/wait.h> 
#include <unistd.h>
#include <sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"cd.h"
#include "echo.h"
 
void split(char* s,char*args[])
{
    // printf("abs");
    int i=0;
    int j=0;
    int k=0;
    int com=0;
    args[j]=(char*)malloc(128*sizeof(char));
    for(;i<s[i]!='\0';i++)
    {
        if(com==0&&s[i]==' ')
        {
            j++;
            k=0;
            if(j>128)
                args=(char**)realloc(args,(j+1)*sizeof(char*));
            args[j]=(char*)malloc(128*sizeof(char));
        }
        else
        {
            if(s[i]=='\"')
            {
                if(com==0)com=1;
                else com=0;
            }
            args[j][k]=s[i];
            k++;
        }

    }
    // if(com==1)
    // {
    //     args[j][k]='\"';
    //     k++;
    //     args[j][k]='\0';
    // }
    j++;
    if(j>128)
        args=(char**)realloc(args,(j+1)*sizeof(char*));
    args[j]=(char*)malloc(128*sizeof(char));
    args[j]=NULL;
    j++;
    // for(int i=0;args[i]!=NULL;i++)
    // {
    //     printf("%d \n",i);

    // }
    // for(int i=0;args[i]!=NULL;i++)
    // {
    //     // printf("%s \n",args[i]);
    //     for(int j=0;args[i][j]!='\0';j++)
    //     {
    //         printf("%c",args[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("%s \n",args[0]);

}


void drivers(char* args[])
{
    // printf("%s\n",args[0]);
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
                    cd1(args);
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
                else if(strcmp(args[0],"echo")==0)
                {
                    echo(args);
                }
                break;
            case 'l':
                if(strcmp(args[0],"ls")==0)
                {
                    
                    int id=fork();
                    if(id==0)
                    {
                        printf("in child process\n");
                        char* a=(char*)malloc(512);
                        a=getenv("PWD");
                        printf("%s\n",a);
                        strcat(a,"/ls");
                        printf("%s\n",a);
                        execv(a,args);
                        printf("end of child process   \n");
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
    else
    {
        printf("null\n");
    }

}

int main(int argc, char const *argv[])
{
    /* code */
    while(1)
    {
        char s[1024];
        printf("boomerOp>>");
        scanf("%[^\n]%*c",s);
        char** args=(char**)malloc(128*sizeof(char*));
        split(s,args);
        // for(int i=0;args[i]!=NULL;i++)
        // {
        //     printf("in main %s \n",args[i]);

        // }
        drivers(args);       

    }
    return 0;
}

