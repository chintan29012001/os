#include<stdio.h>
#include<inttypes.h>
int long_add(int,int,int,int);

int main(int argc, char const *argv[])
{
    /* code */
    int a,b,c,d;
    printf("Enter 4 nos:\n");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    scanf("%d", &d);
    printf(" sum :%d \n",long_add(a,b,c,d));
    printf("Size = %d \n", sizeof(size_t));
    return 0;
}
