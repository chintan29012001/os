// C Program for Message Queue (Reader Process) 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message.h"

// structure for message queue 

int main() 
{ 
	key_t key; 
	int msgid; 
	struct message msg;
	// ftok to generate unique key 
	key = ftok(".", 1); 

	// msgget creates a message queue 
	// and returns identifier 
	msgid = msgget(key, 0666 | IPC_CREAT); 
	// if(msgrcv(msgid, &message, sizeof(struct mesg_buffer), 1, 0) == -1){
	// 	perror("Cannot receive message");
	// 	exit(EXIT_FAILURE);
	// }

	// msgrcv to receive message 
	while(msgrcv(msgid, &msg, sizeof(msg), 1, 0))
    {
		if(strcmp(msg.message,"end")==0)
			break;
        printf("%s \n", 
					msg.message); 
		
			// to destroy the message queue 
    }
	// printf("problem above\n");
	struct msqid_ds info;
	if(msgctl(msgid, IPC_STAT, &info) == -1){
		perror("Cannot retrieve information about the message queue");
		exit(EXIT_FAILURE);
	}
	msgctl(msgid, IPC_RMID, NULL); 	
	exit(0);
	// return 0; 
} 
