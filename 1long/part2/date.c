#include <stdio.h>
//-r last modification time 

int main(int argc, char const *argv[])
{
    /* code */
    printf("%d\n",argc);
    for(int i=0;argv[i]!=NULL;i++)
        printf("%s\n",argv[i]);

    return 0;
}
