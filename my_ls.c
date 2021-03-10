#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "my_ls.h"
#include <stdbool.h>

int openFolder(tkeep *p1, char* p2, bool aop)
{
    DIR *folder;
    struct dirent *entry;
    struct stat filestat;

    folder = opendir(p2);
    if (folder == NULL)
    {
        printf("my_ls: cannot access '%s': No such file or directory\n", p2);
        return 1;
    }
    else
    {
        while( (entry = readdir(folder) ) )
        {
            if ( entry->d_name[0] == '.' && aop == false )
            {}
            else
            {
                if ( my_strcmp(p2, ".") == 0 )
                {
                    lstat(entry->d_name, &filestat);
                }
                else
                {
                    char tmp[100];
                    my_strcpy(tmp, p2);
                    if (p2[my_strlen(p2)] != '/')
                    {
                        my_strcat(tmp, "/");
                    }
                    my_strcat(tmp, entry->d_name);
                    lstat(tmp, &filestat);
                }
                my_strcpy(p1->file[p1->size].name, entry->d_name);
                p1->file[p1->size].type = isDir(filestat.st_mode);
                p1->file[p1->size].time = filestat.st_mtim.tv_sec*1000000000 + filestat.st_mtim.tv_nsec;
                // printf("%-20s %20lld\n", p1->file[p1->size].name, p1->file[p1->size].time);
                p1->size++;
            }
        }
    }

    closedir(folder);

    return 0;
}

void collection(bool aop, bool top, char** p1, int p2 )
{
    tkeep *bunch = malloc( p2 * sizeof(tkeep));
    for(int i = 0; i < p2; i++)
    {
        bunch[i].file = malloc(50 * sizeof(tdirectory));
        bunch[i].size = 0;
        for (int j = 0; j < 50; j++)
        {
            bunch[i].file[j].name = malloc(sizeof(char) * 50);
        }
    }

    for (int i = 0; i < p2 ; i++)
    {
        int check = openFolder(&bunch[i], p1[i], aop);
        if ( check == 0)
        {
            if (top == true)
            {
                sortTime(&bunch[i]);
            }
            else
            {
                sortLex(&bunch[i]);
            }

            if (p2 > 1)
            {
                printf("%s:\n", p1[i]);
            }

            for (int j = 0; j < bunch[i].size; j++)
            {
                // printf("%-20s %5d %20lld\n", bunch[i].file[j].name, bunch[i].file[j].type, bunch[i].file[j].time);
                printf("%s  ", bunch[i].file[j].name);
            }
            printf("\n");
        }
    }

    for (int i = 0; i < p2; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            free(bunch[i].file[j].name);
        }
        free(bunch[i].file);
    }
    free(bunch);
}

int main(int argc, char **argv)
{
    bool aop = false;
    bool top = false;
    int k = 0;
    char* directs[10];

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < my_strlen(argv[i]); j++)
            {
                if(argv[i][j] == 'a')
                {
                    aop = true;
                }
                else if(argv[i][j] == 't')
                {
                    top = true;
                }
            }
        }
        else
        {
            directs[k] = argv[i];
            k++;
        }
    }

    if (k == 0)
    {
        char* op[] = {"."};
        collection(aop, top, op, 1);
    }
    else
    {
        collection(aop, top, directs, k);
    }

    return 0;
}