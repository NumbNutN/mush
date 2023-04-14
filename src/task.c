#include "sh.h"
#include <stdlib.h>

struct _Args NONE_ARGS = 
{
    .argc = 0,
    .argv = NULL
};

void RedirectInputFile(struct _Task* task,char* input)
{
    task->inputFile = input;
}

void RedirectOuputFile(struct _Task* task,char* ouput)
{
    task->outputFile = ouput;
}

void appendArgv(struct _Args* args,char* new_arg)
{
    ++args->argc;
    realloc(args->argv,args->argc*sizeof(char*));
    args->argv[args->argc-1] = new_arg;
}
struct _Task* CreateTask(char* elfFile,struct _Args* args)
{
    struct _Task* task = (struct _Task*)malloc(sizeof(struct _Task));
    task->elfName = elfFile;
    task->args = *args;
    if(args == NULL)
    {
        //只包含文件名一个参数
        task->args = *CreateArgs();
    }
    //添加文件名
    task->args.argv[0] = task->elfName;
    //参数列表末添加NULL
    realloc(args->argv,(args->argc+1)*sizeof(char*));
    args->argv[args->argc] = NULL;
    task->args = *args;
    return task;
}

struct _Args* CreateArgs()
{
    struct _Args* args = (struct _Args*)malloc(sizeof(struct _Args));
    args->argc = 1;
    args->argv = (char**)malloc(sizeof(char*));
    return args;
}