// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main() 
{ 

	int fd1[2]; 
	int fd2[2]; 
	 
	pid_t p; 

	if (pipe(fd1)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 
	if (pipe(fd2)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 

	p = fork(); 
	if (p < 0) 
	{ 
		fprintf(stderr, "fork Failed" ); 
		return 1; 
	} 

	// Parent process 
	else if (p > 0) 
	{ 
		
        char input_str[512];
        fgets(input_str,512,stdin); 
        write(fd1[1], input_str, strlen(input_str)+1); 
		close(fd1[0]);
		close(fd1[1]); 
		wait(NULL); 
		close(fd2[1]);
        char s[512];
        int i=0;
		while(read(fd2[0], &s[i], 1)>0&&i<512)
        {
            i++;
        }
        
		printf("%s", s); 
		close(fd2[0]); 
        return 0;
	} 

	// child process 
	else
	{ 
		close(fd1[1]); 
		char s[512]; 
        int i=0;
        while(read(fd1[0], &s[i], 1)>0&&i<512)
        {
            i++;
        }
        for(i=0;i<strlen(s);i++)
        {
            if(s[i]>='a'&&s[i]<='z')
            {
                s[i]-=32;
            }
        }
		close(fd1[0]); 
		close(fd2[0]); 
		write(fd2[1], s, strlen(s)+1); 
		close(fd2[1]); 

		exit(0); 
	} 
} 
