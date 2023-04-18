#include "sh.tab.h"
#include "sh.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
int main(void) 
{
    mushSuffix();
    yyparse();
    return 0;
}

void loadAElf(struct _Task* task)
{
    char* argv[3];
    for(int i=0;i<3;i++)
        argv[i] = task->args.argv[i];
    do
    {
        if(fork() == 0)
        {
            //修改进程的工作路径
            chdir(CurrentWorkDirectory);
            //标准输入输出文件重定向
            freopen(task->inputFile,"r",stdin);
            freopen(task->outputFile,"w",stdout);
            if(execv(task->elfName,task->args.argv) == -1)
            {
                printf("非法的可执行文件，您可以查看Linux返回的报错信息：\n");
                printf("%s\n",strerror(errno));
            }
        }

        task = task->nextTask;
    
    } while (task != NULL);
    
    task = rootTask;
    do
    {   
        int pchildStatus;
        wait(&pchildStatus);
        task = task->nextTask;
    } while(task != NULL);
    
    task = rootTask;
    do
    {   
        if(task->pipeExit == 1)
        {
            closePipe();
        }
        task = task->nextTask;
    } while(task != NULL);    
}