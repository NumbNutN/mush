#include "sh.h"
#include <stdlib.h>
#include <string.h>


struct _Task* rootTask;
struct _Args NONE_ARGS = 
{
    .argc = 0,
    .argv = NULL
};



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
    memset(task,0,sizeof(struct _Task));
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

    //批处理任务
    task->nextTask = NULL;

    //输入输出文件
    RedirectInputFile(task,STANDARD_INPUT_FILE);
    RedirectOuputFile(task,STANDARD_OUTPUT_FILE);
    return task;
}

struct _Args* CreateArgs()
{
    struct _Args* args = (struct _Args*)malloc(sizeof(struct _Args));
    args->argc = 1;
    args->argv = (char**)malloc(sizeof(char*));
    return args;
}