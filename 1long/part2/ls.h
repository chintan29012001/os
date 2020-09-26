
#include <dirent.h>
//-1 -t -l -Q
//-1 list one file per line
void ls()
{
    struct dirent *de;
    DIR *dr =opendir(".");
    while((de=readdir(dr))!=NULL)
    {
        printf("%s\n",de->d_name);
        printf("%d\n",de->d_type);
    }
    closedir(dr);

}