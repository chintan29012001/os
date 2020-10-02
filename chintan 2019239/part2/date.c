#include <stdio.h>
#include<time.h>
#include <stdlib.h> 
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/types.h>
//-r last modification time 

void date_help()
{
    char* a="/home/chintan/part2/date.help";
    // printf("%s\n",a);
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


void r_date()
{
    
    char buf[256] = {0};
    
    time_t rawtime = time(NULL);
    
    if (rawtime == -1) {
        
        puts("The time() function failed");
        
    }
    
    struct tm *ptm = localtime(&rawtime);
    
    if (ptm == NULL) {
     
        puts("The localtime() function failed");
        
    }
    memset(buf, 0, 256);
	//Wed, 30 Sep 2020 19:44:03 +0530
	strftime(buf, 256, "%a, %d %b %Y %X %z", ptm);
    printf("%s\n",buf);
    

}

void default_date()
{
    char buf[256] = {0};
    
    time_t rawtime = time(NULL);
    
    if (rawtime == -1) {
        
        puts("The time() function failed");
    }
    
    struct tm *ptm = localtime(&rawtime);
    
    if (ptm == NULL) {
     
        puts("The localtime() function failed");
    }
    
    memset(buf, 0, 256);
    ////Wed Sep 30 19:33:07 IST 2020
	strftime(buf, 256, "%a %b %d %X %Z %Y", ptm);
    printf("%s\n",buf);

}
int main(int argc, char const *argv[])
{
    /* code */
    int k=1;
    int* files=(int*)malloc(sizeof(int)*k);
    int flg[3]; //0 --help 1-v 2 -file 
    // 
    

    for(int i=1;argv[i]!=NULL;i++)
    {
        if(strcmp(argv[i],"--help")==0)
        {
            date_help();
            return 0;
        }
        else if(strcmp(argv[i],"-R")==0)
        {
            r_date();
            return 0;
        }
        else
        {
            printf("Invalid\n");
            return 1;
        }
    }
    default_date();   
    return 0;
}
