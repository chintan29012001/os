/*
 * A small program that illustrates how to call the maxofthree function we wrote in
 * assembly language.
 */

#include <stdio.h>
#include <inttypes.h>

int64_t add(int64_t,int64_t);
int64_t sub(int64_t,int64_t);

int main() {
    int64_t a;
    int64_t b;
    printf("Enter integers for addition \n");
    printf("Enter a: \n");
    scanf("%ld",&a);//taking input
    printf("Enter b: \n");
    scanf("%ld",&b);//taking input
    printf("a+b = \n%ld\n",add(a,b));//printing output
    printf("a-b=\n%ld\n",sub(a,b));
    return 0;
}
