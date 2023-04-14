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
    if(fork() == 0)
    {
        //execl("/bin/ls","ls","-l",NULL);
        if(execv(task->elfName,task->args.argv) == -1)
            printf("执行出错");
    }
}