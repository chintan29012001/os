#include<stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include<sys/wait.h> 
#include <sys/types.h> 

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
    printf("roll no: %d avg %.2f \n",details[0],avg/4);
    
}

void func(char x)
{
        FILE *fp=fopen("file.csv","r");
        char buf[1024];
        while(fgets(buf,1024,fp))
        {
                // printf("fo %s\n",buf);
               
            if(buf[0]>='0'&&buf[0]<='9')
            {
                slic(buf,x);

            }
                
        }
        
        fclose(fp);

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
    else
    {
        waitpid(x,&stat,0);
        // printf("%d \n",stat);   
        printf("Parent \n");
        func('B');
    }

    return 0;
}





