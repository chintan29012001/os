#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    /* code */
    char string[100];
    scanf("%s",string);
   // Extract the first token
   char * token = strtok(string, " ");
   // loop through the string to extract all other tokens
   while( token != NULL ) {
      printf( " %s\n", token ); //printing each token
      token = strtok(NULL, " ");
   }
    return 0;
}
