#include "sh.tab.h"
#include "sh.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
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

    if(fork() == 0)
    {
        int pchildStatus;
        //execl("/bin/ls","ls","-l",NULL);
        //execl("./testShell","./testShell","hello","world",NULL);
        if(execv(task->elfName,task->args.argv) == -1)
        {
            printf("非法的可执行文件，您可以查看Linux返回的报错信息：\n");
            printf("%s\n",strerror(errno));
        }

        else
        {
            wait(&pchildStatus);
        }
    }
}