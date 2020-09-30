#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h> 
//cd

void cd_help()
{
    char* a=(char*)malloc(512);
    a=getenv("PWD");
    // printf("%s\n",a);
    strcat(a,"/cd.help");
    // printf("%s\n",a);
    // char * x="cd.help";
    int fd=open(a,O_RDONLY);
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

void cd(const char* a)
{
    if(a==NULL)
        chdir(getenv("HOME"));

    // printf("%s",getenv("HOME"));
    else if(chdir(a)!=0)
    {
        if(chdir(getenv(a))!=0)
        {
            printf("Not valid \n");
        }
    }
}
void cd1(char** argv)
{
    int flg[3];// 0 --help 1 -P 2 files
    for(int i=0;i<3;i++)flg[i]=0;
    int si=0;
    for( si=0;argv[si]!=NULL;si++);
    int* files=(int*)malloc(si*sizeof(int));
    int k=0;
    // for(int i=0;argv[i]!=NULL;i++)
    // {
    //     printf("%s\n",argv[i]);
    // }
    for(int i=1;argv[i]!=NULL;i++)
    {
        if(strcmp(argv[i],"--help")==0)
        {
            flg[0]=1;
            printf("sd\n");
            
        }
        else if(strcmp(argv[i],"-P")==0)
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
        cd_help();
    }
    else if(k>2)
    {
        printf("too many arguments\n");
        
    }
    else if(k>=1)
    {
        char* path=argv[files[0]];
        // struct stat s;
        // int err=stat(path,&s);
        cd(path);
        

    }
    else
    {
        cd(NULL);
    }

    
}