#include<sys/wait.h> 
#include <unistd.h>
#include <sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"cd.h"
#include "echo.h"
#include "history.h"

void exit_help()
{
    char * x="/home/chintan/part2/exit.help";
    int fd=open(x,O_RDONLY);
    char* buf=(char*)malloc(1024);
    int i=0; 
    while(read(fd,&buf[i],1))
    {
        
        if(buf[i]=='\n')
        {
            buf[i]='\0';
            i=0;
            printf("%s\n",buf);
            free(buf);
            buf=(char*)malloc(1024);
        }
        else
            i++;
        
            
    }
    buf[i]='\0';
    free(buf);        
    close(fd);


}
void pwd_help()
{
    char * x="/home/chintan/part2/pwd.help";
    int fd=open(x,O_RDONLY);
    char* buf=(char*)malloc(1024);
    int i=0; 
    while(read(fd,&buf[i],1))
    {
        
        if(buf[i]=='\n')
        {
            buf[i]='\0';
            i=0;
            printf("%s\n",buf);
            free(buf);
            buf=(char*)malloc(1024);
        }
        else
            i++;
        
            
    }
    buf[i]='\0';
    free(buf);        
    close(fd);

}
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
                else if(strcmp(args[0],"cat")==0)
                {
                    int id=fork();
                    if(id==0)
                    {
                        printf("in child process\n");
                        char* a="/home/chintan/part2/cat";
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
            case 'd':
                if(strcmp(args[0],"date")==0)
                {
                    int id=fork();
                    if(id==0)
                    {
                        printf("in child process\n");
                        char* a="/home/chintan/part2/date";
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
                    if(args[1]!=NULL)
                    {
                        if(strcmp(args[1],"--help")==0)
                        {
                            exit_help();
                            return;

                        }

                    }
                    printf("exiting now.... \n");
                    int x=0;
                    for(int i=0;args[i]!=NULL;i++)
                    {
                        if(i==1)
                            x=atoi(args[1]);
                        free(args[i]);

                    }
                    if(args[1]!=NULL)
                        exit(x);
                    else
                        exit(0);
                }
                else if(strcmp(args[0],"echo")==0)
                {
                    echo(args);
                }
                break;
            case 'p':
                if(strcmp(args[0],"pwd")==0)
                {
                    if(args[1]!=NULL)
                    {
                        if(strcmp("--help",args[1])==0)
                        {
                            pwd_help();
                            return;
                        }
                    }
                    char buf[512];
                    printf("%s \n",getcwd(buf,512));
                }
                break;
            case 'l':
                if(strcmp(args[0],"ls")==0)
                {
                    
                    int id=fork();
                    if(id==0)
                    {
                        printf("in child process\n");
                        char* a="/home/chintan/part2/ls";
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
            case 'r':
                if(strcmp(args[0],"rm")==0)
                {
                    
                    int id=fork();
                    if(id==0)
                    {
                        printf("in child process\n");
                        char* a="/home/chintan/part2/rm";
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
            case 'm':
                if(strcmp(args[0],"mkdir")==0)
                {
                    
                    int id=fork();
                    if(id==0)
                    {
                        printf("in child process\n");
                        char* a="/home/chintan/part2/mkdir";
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
                printf("wrong option\n");
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
        // for(int i=0;history[i]!=NULL;i++)
        // {
        //     printf("in main hist %s \n",history[i]);

        // }
        drivers(args,history);       

    }
    return 0;
}

