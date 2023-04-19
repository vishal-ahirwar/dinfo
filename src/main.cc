//Copyright(c)Vishal Ahirwar 2023. 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<time.h>
#include<sys/stat.h>
#include<cstring>

int main(int argc,char**argv)
{
    char path[512];

    DIR*dir=NULL;
    struct dirent*file=NULL;
    struct stat fstat;

    if(argc==1)
    {
        getcwd(path,512);
    };

    dir=opendir(path);
    if(dir==NULL)
    {
        printf("unable to open dir : %s\n",path);
        return -1;
    };

    printf("current path the program running in  :  %s\n\n",path);

    int count=1;
    while((file=readdir(dir))!=NULL)
    {
        stat(file->d_name,&fstat);
        char mode[128];
        if(S_ISDIR(fstat.st_mode))
        {
            strcpy(mode,"DIR");
        }else
        {
            strcpy(mode,"FILE");
        };

        printf("%-10s   %-10s   -->     %-.2fKB     -->     last modification done on : %-10s\n",mode,file->d_name,fstat.st_size/1024.0,ctime(&fstat.st_mtime));
        ++count;
    };

    printf("\nTotal Contents fount : %d\n\n",count);
    closedir(dir);

    return 0;
};
