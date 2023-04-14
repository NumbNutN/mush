#include "sh.tab.h"
#include "sh.h"

#include <unistd.h>
int main(void) 
{
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
        //execl("/bin/ls","ls","-l",NULL);
        execl("./testShell","./testShell","hello","world",NULL);
        // if(execv(task->elfName,task->args.argv) == -1)
        //     printf("执行出错");
    }
}