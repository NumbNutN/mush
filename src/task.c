#include "sh.h"
#include <stdlib.h>

struct _Args NONE_ARGS = 
{
    .argc = 0,
    .argv = NULL
};

void appendArgv(struct _Args* args,char* new_arg)
{
    ++args->argc;
    realloc(args->argv,args->argc*sizeof(char*));
    args->argv[args->argc-1] = new_arg;
}

void RedirectInputFile(struct _Task* task,char* input)
{
    task->inputFile = input;
}

void RedirectOuputFile(struct _Task* task,char* ouput)
{
    task->outputFile = ouput;
}

struct _Task* CreateTask(char* elfFile,struct _Args* args)
{
    struct _Task* task = (struct _Task*)malloc(sizeof(struct _Task));
    task->elfName = elfFile;

    if(args == NULL)
    {
        task->args = NONE_ARGS;
        return task;
    }
    realloc(args->argv,(args->argc+1)*sizeof(char*));
    args->argv[args->argc] = NULL;
    task->args = *args;
}

struct _Args* CreateArgs(char* arg)
{
    struct _Args* args = (struct _Args*)malloc(sizeof(struct _Args));
    args->argc = 1;
    args->argv = (char**)malloc(sizeof(char*));
    args->argv[0] = arg;
    return args;
}