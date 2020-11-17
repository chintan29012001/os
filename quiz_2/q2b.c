#include <stdio.h>
#include <string.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include "message.h"
 
int main(int argc, char const *argv[])
{
    /* code */
    FILE *fp;
    key_t key;
    int msgid;
    struct message toke;
    fp=fopen("para2.txt","r");
    if(fp==NULL)
        return 1;
    
    
    key=ftok(".",1);
    msgid=msgget(key,0666|IPC_CREAT);
    toke.type=1;
    char buf[512];
    // printf("sending data from b \n");
    while(fgets(buf,512,fp))
    {
        char* temp=strtok(buf," ");
        while(temp!=NULL)
        {
           strcpy(toke.message,temp);
           msgsnd(msgid,&toke,sizeof(toke),0);
        //    printf("%s \n",temp);
           temp=strtok(0," ");
           
        }
        // printf("data sent");
    }
    strcpy(toke.message,"\n\n");
    msgsnd(msgid,&toke,sizeof(toke),0);
    
    return 0;
}
