#include <stdio.h> 
#include <time.h>        
#include <string.h>

#define BUF_LEN 256

int main(void) {
    
    char buf[BUF_LEN] = {0};
    
    time_t rawtime = time(NULL);
    
    if (rawtime == -1) {
        
        puts("The time() function failed");
        return 1;
    }
    
    struct tm *ptm = localtime(&rawtime);
    
    if (ptm == NULL) {
     
        puts("The localtime() function failed");
        return 1;
    }

    strftime(buf, BUF_LEN, "%d/%m/%Y", ptm);
    puts(buf);
    
    memset(buf, 0, BUF_LEN);
	//Wed Sep 30 19:33:07 IST 2020
    strftime(buf, BUF_LEN, "%a %b %d %X %Z %Y", ptm);
    printf("%s\n",buf);
	//Wed, 30 Sep 2020 19:44:03 +0530
	strftime(buf, BUF_LEN, "%a, %d %b %Y %X %z", ptm);
    printf("%s\n",buf);
    puts(buf);

    return 0;
}