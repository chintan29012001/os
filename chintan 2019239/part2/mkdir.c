#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h> 

void help()
{
    char * x="/home/chintan/part2/mkdir.help";
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

void def(const char* argv[],int si,int files[],int v)
{

    for(int i=0;i<si;i++)
    {
        if(mkdir(argv[files[i]],0700)==-1)
        {
            printf("mkdir cannot make '%s' dir \n",argv[files[i]]);
        }
        else if(v==1)
        {
            printf("mkdir created a dir '%s'\n",argv[files[i]]);
        }

    }    

}

int main(int argc, char const *argv[])
{
    /* code */
    
    int k=1;
    int* files=(int*)malloc(sizeof(int)*5);
    int flg[3]; //0 --help 1-v 2 -file 
    for(int i=0;i<3;i++)flg[i]=0;
    for(int i=1;argv[i]!=NULL;i++)
    {
        if(strcmp(argv[i],"--help")==0)
        {
            flg[0]=1;
            help();
        }
        else if(strcmp(argv[i],"-v")==0)
        {
            flg[1]=1;
        }
        else
        {
            if(k>5)
                files=(int*)realloc(files,sizeof(int)*k);
            files[k-1]=i;
            k++;
        }
    }
    if(flg[0]==1)
    {
        help();

    }
    else
    {
        if(flg[1]==1)
        {
            def(argv,k-1,files,1);
        }
        else
        {
            def(argv,k-1,files,0);
        }
    }

    return 0;
}
