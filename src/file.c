#include "sh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>


void RedirectInputFile(struct _Task* task,char* input)
{
    task->inputFile = input;
}

void RedirectOuputFile(struct _Task* task,char* ouput)
{
    task->outputFile = ouput;
}

void createPipeBetweenTasks(struct _Task* outputTask,struct _Task* InputTask)
{
    if(mkfifo(DEFAULT_MUSH_PIPE,0644) == -1)
    {
        printf("管道创建失败，您可以查看Linux返回的报错信息：\n");
        printf("%s\n",strerror(errno));
    }
    RedirectOuputFile(outputTask,DEFAULT_MUSH_PIPE);
    RedirectInputFile(InputTask,DEFAULT_MUSH_PIPE);

    //建立批处理batch关系
    outputTask->nextTask = InputTask;
    //给输入任务管道释放标志位
    outputTask->pipeExit = 1;
}

void closePipe()
{
    if(unlink(DEFAULT_MUSH_PIPE) != 0)
    {
        printf("管道删除失败，您可以查看Linux返回的报错信息：\n");
        printf("%s\n",strerror(errno));
    }
}
