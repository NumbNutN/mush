#include <stdlib.h>
#include <string.h>

#include "sh.h"
#include "sh.tab.h"

#define MAX_PATH_SIZE 50
char* WorkPath = "/bin";

// size_t _pathFindTop(char* path)
// {
//     size_t idx = 0;
//     do
//     {
//         idx++;
//     } while (path[idx]!='\0');
//     return idx;
// }

void pathAppendSubDirectory(char** oriPath,char* appendPath)
{
    *oriPath = strcat(*oriPath,appendPath);
}

void pathPopSubDirectory(char** oriPath)
{
    size_t idx = strlen(oriPath);
    do{
        idx--;
    } while(*oriPath[idx] != '/');
    
    do{
        idx++;
        oriPath[idx] = '\0';
    } while(idx<MAX_PATH_SIZE);
}

void pathAppend(char** oriPath,enum _Path type,char* subPath)
{
    switch(type)
    {
        case PARENT:
            pathPopSubDirectory(oriPath);
        break;
        case CURRENT:
        break;
        case SUB:
            pathAppendSubDirectory(oriPath,subPath);
        break;
    }
}

void createNewPath(char** newPath,enum _Path type)
{
    *newPath = (char*)malloc(sizeof(char)*MAX_PATH_SIZE);
    memset(*newPath,0,sizeof(char)*MAX_PATH_SIZE);
    switch(type)
    {
        case ROOT:
        {
            *newPath[0] = '/';
        }
        break;
        default:
        {
            strcpy(*newPath,WorkPath);
            pathAppend(newPath,type,NULL);
        }
        break;
    }
}

void mushSuffix()
{
    printf("(mush)%s",WorkPath);
}