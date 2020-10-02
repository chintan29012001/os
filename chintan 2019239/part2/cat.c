#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>



//-n no of lines
//-E display $ eod
static int in=0;

void cat(int flg[],char buf[])
{
    
        if(flg[0]==1)
        {
            
            printf("\t %d ",in);
            in++;
        }
        printf("%s",buf);
        if(flg[1]==1)
        {
            printf(" $");
            
        }
        printf("\n");

    

}
int funcDir(const char* x,int flg[])
{
        struct dirent *de;
        DIR *dr=opendir(x);
        if(dr==NULL)
            return -1;
        printf("cat: %s: Is a directory",de->d_name);
        return 0;

}
int funcFile(const char** args,int flg[],int* files,int si)
{

    for(int i=0;i<si;i++)
    {
        const char* x=args[files[i]];
        int fd=open(x,O_RDONLY);
        if(fd==-1)
            return funcDir(args[files[i]],flg);
        char* buf=(char*)malloc(1024);
        int i=0; 
        while(read(fd,&buf[i],1))
        {
            
            if(buf[i]=='\n')
            {
                buf[i]='\0';
                i=0;
                cat(flg,buf);
                free(buf);
                buf=(char*)malloc(1024);
            }
            else
                i++;                
        }
        buf[i]='\0';
        cat(flg,buf);
        free(buf);        
        close(fd);
    }
        return 0;

}



int main(int argc, char const *argv[])
{
    /* code */
    int si=0;
    int i=0;
    // char** files;
    for(i=0;argv[i]!=NULL;i++);
    si=i;
    int flg[3];// 0 -n 1 -E 2 dir/file 3 wrong option 
    int *files=(int*)malloc(10*sizeof(int));
    int k=0;
    for(int i=0;i<3;i++)flg[i]=0; 
    for(i=1;argv[i]!=NULL;i++)
    {
        
        if(strcmp(argv[i],"-n")==0)
        {
            flg[0]=1;
        }
        else if(strcmp(argv[i],"-E")==0)
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
    if(flg[2]==1)
    {
        in=1;
        
        if(funcFile(argv,flg,files,k)==-1)
            printf("invalid \n");
        

    }
    else
    {
        char buf[1024];
        in=1;
        while(strcmp(buf,"exit")!=0)
        {
            scanf("%s[^\n]%*c",buf);
            if(buf[0]=='e')
            {
                if(strcmp(buf,"exit")==0)
                    break;
            }
            cat(flg,buf);

        }

    } 
    return 0;
}
