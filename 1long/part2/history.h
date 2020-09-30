
#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h> 

void history_append(char** x)
{
    char* a=(char*)malloc(512);
    a=getenv("PWD");
    // printf("%s\n",a);
    strcat(a,"/history.txt");
    // printf("%s\n",a);
    // char * x="cd.help";
    int fd=open(a,O_CREAT|O_WRONLY|O_APPEND|O_DSYNC,0700);
    char bu[1024];
    for(int i=0;x[i]!=NULL;i++)
    {
        int si=0;
        for(;x[i][si]!='\0';si++);
        write(fd,x[i],si);
        write(fd,"\n",1);
    }
    close(fd);

}
void history_read()
{
    char* a=(char*)malloc(512);
    a=getenv("PWD");
    // printf("%s\n",a);
    strcat(a,"/history.txt");
    // printf("%s\n",a);
    // char * x="cd.help";
    int fd=open(a,O_CREAT|O_RDONLY,0700);
    char* buf=(char*)malloc(1024);
    int i=0;
    int k=0;
    while(read(fd,buf[i],1)!=0)
    {
        if(buf[i]=='\n')
        {
            buf[i]='\0';
            i=0;
            printf("%d %s",k+1,buf);
            k++;
        }
            else
                i++;

    }
    close(fd);

}
char** history_clear(char** x)
{
    free(x);
    x=(char**)malloc(512*sizeof(char*));
    return x;
}
 


char** history(char** argv,char** history)
{
    
    int si=0;
    for( si=0;argv[si]!=NULL;si++);
    int* files=(int*)malloc(si*sizeof(int));
    int k=0;
    for(int i=1;argv[i]!=NULL;i++)
    {
        if(strcmp(argv[i],"-c")==0)
        {
            
            history=history_clear(history);
            return history;
        }
        else if(strcmp(argv[i],"-a")==0)
        {
            history_append(history);
            return history;
        }
        else
        {
            history_read();
            for(int i=0;history[i]!=NULL;i++)
            {
                printf("%s\n",history[i]);
            }
        }
    }
    
}