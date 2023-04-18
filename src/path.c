#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sh.h"
#include "sh.tab.h"

#define MAX_PATH_SIZE 50
char* CurrentWorkDirectory = "/bin/";


void pathAppendSubDirectory(char** oriPath,char* appendPath)
{
    oriPath = strcat(*oriPath,appendPath);
}

void pathPopSubDirectory(char* oriPath)
{
    size_t idx = strlen(oriPath) - 1;
    do{
        idx--;
    } while(oriPath[idx] != '/');
    
    do{
        idx++;
        oriPath[idx] = '\0';
    } while(idx<MAX_PATH_SIZE);
}

void pathAddSlah(char* path)
{
    size_t idx = strlen(path);
    path[idx] = '/';
}

void pathAppend(char* oriPath,enum _Path type,char* subPath)
{
    switch(type)
    {
        case PARENT:
            pathPopSubDirectory(oriPath);
        break;
        case CURRENT:
        break;
        case SUB:
        case LEAF:
            pathAppendSubDirectory(&oriPath,subPath);
        break;
    }
}

char* createNewPath(enum _Path type)
{
    char* newPath = (char*)malloc(sizeof(char)*MAX_PATH_SIZE);
    memset(newPath,0,sizeof(char)*MAX_PATH_SIZE);
    switch(type)
    {
        case ROOT:
        {
            newPath[0] = '/';
        }
        break;
        default:
        {
            strcpy(newPath,CurrentWorkDirectory);
            pathAppend(newPath,type,NULL);
        }
        break;
    }
    return newPath;
}

void mushSuffix()
{
    printf("(mush)%s\t",CurrentWorkDirectory);
}

void changeCWD(char* newCWD)
{
    char testCmd[20];
    sprintf(testCmd,"test -d %s",newCWD);
    if(system(testCmd))
    {
        printf("不存在的路径\n");
        return;
    }
    
    if(newCWD[strlen(newCWD) - 1] != '/')
        newCWD[strlen(newCWD)] = '/';
    CurrentWorkDirectory = newCWD;
}