#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    /* code */
    FILE *fp;
    fp=fopen("para1.txt","r");
    if(fp==NULL)
        return 1;
    char buf[512];
    while(fgets(buf,512,fp))
    {
        printf("%s",buf);
    }
    printf("\n");




    return 0;
}
