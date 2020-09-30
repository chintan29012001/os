// remove quotes and backslash

#include<sys/wait.h> 
#include <unistd.h>
#include <sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <dirent.h>
#include <fcntl.h> 

void echo_help()
{
    char * x="echo.help";
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

void def(char** argv,int* files,int si,int n)
{
    for(int i=0;i<si;i++)
    {
        printf("%s ",argv[files[i]]);

    }
    if(n==0)
        printf("\n");
}

void echo(char** argv)
{
    // printf("in echo\n");
    int flg[3];// 0 --help 1 -n 2 files
    for(int i=0;i<3;i++)flg[i]=0;
    int si=0;
    for( si=0;argv[si]!=NULL;si++);
    int* files=(int*)malloc(si*sizeof(int));
    int k=0;
    for(int i=1;argv[i]!=NULL;i++)
    {
        if(strcmp(argv[i],"--help")==0)
        {
            flg[0]=1;
            
        }
        else if(strcmp(argv[i],"-n")==0)
        {
            flg[1]=1;
        }
        else
        {
            flg[2]=1;
            files[k]=i;
            k++;
        }
    }
    if(flg[0]==1)
    {
        echo_help();
    }
    else
    {
        def(argv,files,k,flg[1]);
    }
    // for(int i=0;argv[i]!=NULL;i++)
    // {
    //     printf("%s ",argv[i]);

    // }

    


}