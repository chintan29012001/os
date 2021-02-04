#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/file.h>
#include <errno.h>
#include <fcntl.h>



int main(){   
    
    int c;   
    static struct termios oldt, newt;
    FILE *fptr;
    // struct flock filelock;
    fptr = fopen("hello.txt","r+");
    if(fptr==NULL)
    {
        fptr=fopen("hello.txt","w+");
    }
    int fd=fileno(fptr);
    if (lockf(fd, F_TLOCK, 0) == -1) 
    {
        printf("File Waring file already in use \n");
    }
    
    tcgetattr( STDIN_FILENO, &oldt);
    
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);          
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    char* x=malloc(1024*sizeof(char));
    int i=0;
    while (i<1024&&fread(&x[i],sizeof(char),1,fptr)>0)
    {
        putchar(x[i]);
        i++;
    }
    
    
    while((c=getchar())&&c!='/')      
    {
        
        putchar(c);                 
        
        x[i]=c;
        i++;
        

    }

    
    rewind(fptr);
    fputs(x,fptr);
    
    if (lockf(fd, F_ULOCK, 0) == -1) {
    printf("unlock error");
    
  }
    fclose(fptr);
    
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);


    return 0;
}
