#include<sys/wait.h> 
#include <unistd.h>
#include <sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"cd.h"
#include "echo.h"
#include "history.h" 
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


void drivers(char* args[],char** his)
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
                    // for(int i=0;args[i]!=NULL;i++)
                    // {
                    //     printf("%s\n",args[i]);
                    // }
                    cd1(args);
                }
                break;
            case 'h':
                 if(strcmp(args[0],"history")==0)
                {
                    // for(int i=0;args[i]!=NULL;i++)
                    // {
                    //     printf("%s\n",args[i]);
                    // }
                    history(args,his);
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
    char** history=(char**)malloc(512*sizeof(char*));
    int i=0;
    char* s=(char*)malloc(512*sizeof(char));
    while(1)
    {
        
        printf("boomerOp>>");
        scanf("%[^\n]%*c",s);
        
        char** args=(char**)malloc(128*sizeof(char*));
        split(s,args);
        if(i>512)
            history=(char**)realloc(history,i*sizeof(char*));
        else
        {
            if(s!=NULL)
            {
                history[i]=s;
                s=(char*)malloc(512*sizeof(char));
                i++;
            }
        }
        for(int i=0;history[i]!=NULL;i++)
        {
            printf("in main hist %s \n",history[i]);

        }
        drivers(args,history);       

    }
    return 0;
}

