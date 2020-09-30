#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include<string.h>
#include <unistd.h> 
#include <stdlib.h>

//-f force non existent and dont give an error
//-i prompt before every removal

int isDir(const char* path)
{
    if(path==NULL)
        return 0;
    struct stat s;
    int err=stat(path,&s);
    if(err==0&& S_ISDIR(s.st_mode))
    {
        return 1;
    }
    else 
    {
        return 0;
    }
    return 0;
}

void _f(const char* argv[],int files[],int si,int f)
{
    for(int i=0;i<si;i++)
    {
        if(isDir(argv[files[i]])==0)
        {
            if(f==1)
                remove(argv[files[i]]);
            else if(f==2)
            {
                if(remove(argv[files[i]])!=0)
                {
                    printf("rm cannot delete %s \n",argv[files[i]]);
                }

            }
            else
            {
                printf("Do you want to remove (y/n) %s\n",argv[files[i]]);
                char buf[10];
                scanf("%s",buf);
                if(strcmp(buf,"yes")==0||strcmp(buf,"y")==0)
                {
                    if(remove(argv[files[i]])!=0)
                    {
                        printf("rm cannot delete %s \n",argv[files[i]]);
                    }
                }

            }
        }
        else
        {
            
            printf("rm: cannot remove '%s' :Is a Directory\n",argv[files[i]]);
            
        }
    }

    

}

int main(int argc, char const *argv[])
{
    /* code */
    int si=0;
    int i=0;
    for(i=0;argv[i]!=NULL;i++);
    si=i;
    int flg[3];// 0 -f 1 -i 2 file
    int k=1;
    int* files=(int*)malloc((k)*sizeof(int));;
    for( i=0;i<3;i++)flg[i]=0;       
    for(i=1;argv[i]!=NULL;i++)
    {            
        if(strcmp(argv[i],"-f")==0)
        {
            flg[0]=1;
        }
        else if(strcmp(argv[i],"-i")==0)
        {
            flg[1]=1;                            
        }
        else
        {
            flg[2]=1;
            if(k>1)
                files=(int*)realloc(files,(k)*sizeof(int));
            files[k-1]=i;
            k++;
        }            
    }
    if(flg[2]==0)
    {
        if(flg[0]==0)
        {
            printf("Invalid\n");
        }

    }
    else
    {
        if(flg[0]==0)
        {
            if(flg[1]==1)
            {
                _f(argv,files,k-1,0);

            }
            else
            {
                _f(argv,files,k-1,2);
            }

        }
        else
        {
            _f(argv,files,k-1,1);

        }
    }
        

    return 0;
}
