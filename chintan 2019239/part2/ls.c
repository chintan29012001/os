
#include <dirent.h>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
//-1 -t -l -Q
//-1 list one file per line
//to do sort
// int comp(const char *a,const char* b)
// {
//     printf("%s\n",a);
//     return strcmp((char*)a,(char*)b);
// }
void print(char** s)
{
    int i=0;
    for(i=0;s[i]!=NULL;i++);
    int si=i;
    // qsort(s,si,10,comp);
    for(int i=0;s[i]!=NULL;i++)
    {
        if(s[i][0]!='.')
        {
            printf("%s",s[i]);
            
        }
    }

}


char** list_all(char** lines)
{
    // printf("asa");
    struct dirent *de;
    DIR *dr =opendir(".");
    int i=1;
    if(dr==NULL)
    {
        printf("not valid dir");
        return NULL;
    }
    while((de=readdir(dr))!=NULL)
    {
        if(i>256)
            lines=(char**)realloc(lines,sizeof(char*)*i);
        // printf("%ld\n",sizeof(de->d_name)*sizeof(char));
        lines[i-1]=(char*)malloc(sizeof(256)*sizeof(char));
        lines[i-1]=strcpy(lines[i-1],de->d_name);
        i++;
        
    }
    if(i>256)
        lines=(char**)realloc(lines,sizeof(char*)*i);
    lines[i]=NULL;
    closedir(dr);
    return lines;
}
void ls(char** s)
{
    for(int i=0,k=0;s[i]!=NULL;i++)
    {
        if(k%5==0&&k!=0)
        {
            printf("\n");
            k++;
        }
        if(s[i][0]!='.'&&s[i][0]!='\0')
        {
            printf("%s\t",s[i]);
            k++;
        }

    }
    printf("\n");


}
void _1(char** s)
{
    for(int i=0,k=0;s[i]!=NULL;i++)
    {
        if(s[i][0]!='.')
        {
            // printf("%s\n",s[i]);
            char* temp=(char*)malloc(270);
            temp=strcpy(temp,s[i]);
            temp=strcat(temp,"\n");
            s[i]=temp;
        }
    }
}
void _q(char** s)
{
    for(int i=0,k=0;s[i]!=NULL;i++)
    {
        if(s[i][0]!='.')
        {
            char* temp=(char*)malloc(270);
            char* t="\"";
            temp=strcpy(temp,t);
            temp=strcat(temp,s[i]);
            temp=strcat(temp,t);
            s[i]=temp;
            
        }
    }

}
int main(int argc, char const *argv[])
{
    /* code */
    // printf("asab");
    // printf(" in ls now\n ");
    // for(int i=0;argv[i]!=NULL;i++)
    // {
    //     printf("%s \n",argv[i]);
    // }
    int si=0;
    int i=0;
    // printf("%s\n",argv[0]);
    char** files=(char**)malloc(256*sizeof(char*));
    for(i=0;argv[i]!=NULL;i++);
    si=i;
    files=list_all(files);
    // printf("%d\n",si);
    if(files==NULL)
    {
        return 1;
    }
    if(si==1)
    {
        ls(files);
    }
    else if(si==2)
    {
        if(strcmp(argv[1],"-1")==0)
        {
            _1(files);
            print(files);
        }
        else if(strcmp(argv[1],"-Q")==0)
        {
            _q(files);
            ls(files);
        }
        else
        {
            printf("Invalid arguments\n");
        }

    }
    else if(si==3)
    {
        if(strcmp(argv[1],"-1")==0)
        {
            if(strcmp(argv[2],"-Q")==0)
            {
                _q(files);
                _1(files);
                // print(files);
                
                print(files);

            }
            else
            {
                printf("Invalid arguments \n");
            }
        }
        else if(strcmp(argv[1],"-Q")==0)
        {
            if(strcmp(argv[2],"-1")==0)
            {
                _q(files);
                _1(files);
                // print(files);
                print(files);

            }
            else
            {
                printf("Invalid arguments \n");
            }

        }
        else
        {
            printf("Invalid arguments \n");
        }
    }
    return 0;
}
