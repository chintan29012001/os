#include<stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include<sys/wait.h> 
#include <sys/types.h> 
#include <fcntl.h> 
#include<sys/stat.h>

void slic(char ar[],char sec)
{
    int j=0;
    int i=0;
    int details[5];
    for(int i=0;i<5;i++)
        details[i]=0;
    int y=0;
    int x=0;
    for(int k=0;ar[k]!='\0';k++)
    {
        if(ar[k]==sec)
        {
            x=1;
            break;
        }
    
    }
    if(x==0)
        return;

    for(i=0;ar[i]!='\0';)
    {
        for(j=i;ar[j]!=','&&ar[j]!='\0';)
        {
            if(ar[j]>='0'&&ar[j]<='9')
            {
                details[y]=details[y]*10+ (ar[j]-'0');
            }

            j++;
        }
        if(ar[j]!='\0')
        {
            if(ar[i]>='0'&&ar[i]<='9')
                y++;
            j=j+1;
            i=j;
        }
        else
            break;
    }
    
    // printf("rno. %d a1: %d \n",details[0],details[1]);
    float avg=0;
    for(i=1;i<5;i++)
    {
        avg+=details[i];
    }
    printf("%c roll no:%d \t a1:%d \t a2:%d \t a3:%d \t a4:%d \t avg %.2f \n",sec,details[0],details[1],details[2],details[3],details[4],avg/4);
    
}

void func(char x)
{
        int fd=open("file.csv",O_RDONLY);
        if(fd==-1)
        {
            printf("File not found");
            return;
        }
        // FILE *fp=fopen("file.csv","r");
        char buf[1024];
        char t[]="itStudent,ID,Section-Number,Assignment-1,Assignment-2,Assignment-3,Assignment-4";
        read(fd,buf,sizeof(t)+1);
        for(int i=0;i<1024;i++)
            buf[i]='\0';
        int i=0; 
        
        while(read(fd,&buf[i],1))
        {
            // if(buf[0]<'0'&&buf[0]>'9')
            // {
            //     printf("%s",buf);
            // }
            if(buf[i]=='\n')
            {
                
                // printf("%s",buf);
                i=0;
                if(buf[0]>='0'&&buf[0]<='9')
                {
                    slic(buf,x);
                    for(int i=0;i<500;i++)
                        buf[i]='\0';

                }
            }
            else
                i++;
            
                
        }
        // printf("abc %s",buf);
        if(buf[0]>='0'&&buf[0]<='9')
        {
            slic(buf,x);

        }
        
        close(fd);

}
int main(int argc, char const *argv[])
{
    /* code */
    // printf("fml");
    int x=fork();
    int stat;
    
    if(x==0)
    {
        // main("","");

        printf("Child \n");
        func('A');
        exit(0);
    }
    else if(x<0)
    {
        printf("cannot make a child \n");
        return 1;
    }
    else
    {
        waitpid(x,&stat,0);
        // printf("%d \n",stat);   
        printf("Parent \n");
        func('B');
    }

    return 0;
}





