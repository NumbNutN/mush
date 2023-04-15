#include <stdlib.h>
#include <string.h>

#include "sh.tab.h"

#define MAX_PATH_SIZE 50
char* WorkPath;

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
}

void pathAppend(char** oriPath,int type)
{
    switch(type)
    {
        case PARENT_DIRECTORY:
            
        break;
    }
}

char* createNewPath(int type)
{
    char* currentPath = (char*)malloc(sizeof(char)*MAX_PATH_SIZE);
    memset(currentPath,0,sizeof(char)*MAX_PATH_SIZE);
    strcpy(currentPath,WorkPath);
    switch(type)
    {
        case PARENT_DIRECTORY:
            pathPopSubDirectory(&currentPath);
        break;
        case CURRENT_DIRECTORY:
        break;
    }
    return currentPath;
}