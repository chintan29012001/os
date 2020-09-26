#include<stdio.h>
void main(int argc, char const *argv[])
{
    char x[64];
    long int* a=(long int*)x;
    for(long int i=0;i<8;i++)
    {
        *a=(i+256);
        a++;
    }
    a=(long int*)x;
    for(int i=0;i<8;i++)
    {
        printf("no. is %ld \n",*a);
        a++;
    }
    // for(int i=0;i<64;i++)
    // {
    //     printf("val at %d is %d \n",i,x[i]);
    //     if((i+1)%8==0&&i!=0)
    //         printf("\n");
    // }
    int* b=(int*)x;
    for(int i=0;i<16;i++)
    {
        *b=(i+256);
        b++;
    }
    b=(int*)x;
    for(int i=0;i<16;i++)
    {
        printf("no. is %d \n",*b);
        b++;
    }
    // for(int i=0;i<64;i++)
    // {
    //     printf("val at %d is %d \n",i,x[i]);
    //     if((i+1)%4==0)
    //         printf("\n");
    // }



}
