
#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h> 

void history_help()
{
    char * x="/home/chintan/part2/history.help";
    int fd=open(x,O_RDONLY);
    if(fd==-1)
    {
        printf("cannot open history.txt\n");
        return;
    }
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

void history_append(char** x)
{
    char* a="/home/chintan/part2/history.txt";
    // printf("%s\n",a);
    // char * x="cd.help";
    int fd=open(a,O_CREAT|O_WRONLY|O_APPEND|O_DSYNC,0700);
    if(fd==-1)
    {
        printf("cannot open history.txt\n");
        return;
    }
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
    char* a="/home/chintan/part2/history.txt";
    int fd=open(a,O_RDONLY);
    if(fd==-1)
    {
        printf("cannot open history.txt\n");
        return;
    }
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

 


char** history(char** argv,char** history)
{
    printf("in his\n");
    int si=0;
    for( si=0;argv[si]!=NULL;si++);
    int* files=(int*)malloc(si*sizeof(int));
    int k=0;
    for(int i=1;argv[i]!=NULL;i++)
    {
        if(strcmp(argv[i],"--help")==0)
        {
            
            history_help();
            return history;
        }
        else if(strcmp(argv[i],"-a")==0)
        {
            history_append(history);
            return history;
        }
        else
        {
            printf("invalid flag");
            return history;
        }
        
    }
    history_read();
    for(int i=0;history[i]!=NULL;i++)
    {
        printf("%s\n",history[i]);
    }
    
}