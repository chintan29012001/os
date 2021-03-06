#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define MAX_MESSAGE_SIZE 100
#define LOCAL       "./sockC"

int main(int argc, char const *argv[])
{
    
    struct sockaddr_un address;
	int fd;
	char message[MAX_MESSAGE_SIZE];
	message[MAX_MESSAGE_SIZE -1] = '\0';

	// Setting my domain
	address.sun_family = AF_UNIX;
	memcpy(address.sun_path, LOCAL, strlen(LOCAL) + 1); 

	// Make a socket file
	if((fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1){
        		perror("Socket cannot be instantiated");
		exit(EXIT_FAILURE);
	}

	// Bind
	unlink(LOCAL);
	if(bind(fd, (struct sockaddr*) &address, sizeof(address)) == -1){
		perror("Cannot bind socket");
		exit(EXIT_FAILURE);
	}

	// Emitter
    struct sockaddr_un emitter;
	socklen_t len;
	int c=0;
	size_t size;
	do{
		memset(message, 0, MAX_MESSAGE_SIZE);
		size = recvfrom(fd, message, MAX_MESSAGE_SIZE, 0, (struct sockaddr *) &emitter, &len);
		if(size == -1) { perror("Receiver"); exit(EXIT_FAILURE); }
        if(strcmp(message, "\n\n") != 0)
		    printf("%s ",message);
		else
		{
			c++;
		}
	}while(c != 2);
    return 0;
}
