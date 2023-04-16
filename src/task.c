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
    args->argv = realloc(args->argv,args->argc*sizeof(char*));
    args->argv[args->argc-1] = new_arg;
}

void fillAbsolutePath(char* elfFile)
{
    
}
struct _Task* CreateTask(char* elfFile,struct _Args* args)
{
    struct _Task* task = (struct _Task*)malloc(sizeof(struct _Task));
    task->elfName = elfFile;
    if(args == NULL)
    {
        //只包含文件名一个参数
        task->args = *CreateArgs();
    }
    else
        task->args = *args;
    //添加文件名
    task->args.argv[0] = task->elfName;
    //参数列表末添加NULL
    task->args.argv = realloc(task->args.argv,(task->args.argc+1)*sizeof(char*));
    task->args.argv[task->args.argc] = NULL;
    return task;
}

struct _Args* CreateArgs()
{
    struct _Args* args = (struct _Args*)malloc(sizeof(struct _Args));
    args->argc = 1;
    args->argv = (char**)malloc(sizeof(char*));
    return args;
}