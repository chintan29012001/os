#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>

int main(int argc, char const *argv[])
{
    /* code */
    int x;
    scanf("%d",&x);
    mkdir("leh",x);
    return 0;
}
