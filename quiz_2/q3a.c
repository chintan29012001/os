#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#define MAX_MESSAGE_SIZE 100
#define LOCAL       "./sockA"
#define DESTINATION "./sockC"
int main(int argc, char const *argv[])
{
    FILE *fp;
    fp=fopen("para1.txt","r");
    if(fp==NULL)
        return 1;
    
    
    struct sockaddr_un address;
	int fd;

	address.sun_family = AF_UNIX;
	memcpy(address.sun_path, LOCAL, strlen(LOCAL) + 1); 

	// Make a socket file
	if((fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1){
		perror("Socket cannot be instantiated");
		exit(EXIT_FAILURE);
	}

	unlink(LOCAL);
	if(bind(fd, (struct sockaddr*) &address, sizeof(address)) == -1){
		perror("Cannot bind socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_un destination;
	destination.sun_family = AF_UNIX;
	memcpy(destination.sun_path, DESTINATION, strlen(DESTINATION) + 1); 

	char buf[512];
    while(fgets(buf,512,fp))
    {
        char* temp=strtok(buf," ");
        while(temp!=NULL)
        {
           sendto(fd, temp, strlen(temp)+1, 0, (struct sockaddr*) &destination, sizeof(destination));
           temp=strtok(0," ");
           
        }
        // printf("data sent");
    }
    // sendto(fd, "\n\n", strlen("\n\n")+1, 0, (struct sockaddr*) &destination, sizeof(destination));

    
    return 0;
}
