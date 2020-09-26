
#include <dirent.h>
//-1 -t -l -Q
//-1 list one file per line

void print(char s[])
{
    printf("%s",s);

}
void ls()
{
    struct dirent *de;
    DIR *dr =opendir(".");
    int i=0;
    while((de=readdir(dr))!=NULL)
    {
        if(de->d_name[0]=='.')
            continue;
        if(i%5==0&&i!=0)
            printf("\n");
        printf("%s \t",de->d_name);
        i++;
        
    }
    printf("\n");
    closedir(dr);

}