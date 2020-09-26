#include<stdio.h>
int main(int argc, char const *argv[])
{
    /* code */
    FILE *ptr =fopen("x.txt","w");
    char x[]={"chintan"};
    fprintf(ptr,"%s",x);
    fclose(ptr);
    return 0;
}
