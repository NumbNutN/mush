#ifndef _SH_H
#define _SH_H

typedef struct _Args{
    int argc;
    char** argv;
} Args,*pArgs;

typedef struct _Task{

    char* elfName;
    struct _Args args;
    char* inputFile;
    char* outputFile;
}Task,*pTask;

enum _Path{
    PARENT,
    CURRENT,
    ROOT,
    SUB
};


void appendArgv(struct _Args* args,char* new_arg);
void RedirectInputFile(struct _Task* task,char* input);
void RedirectOuputFile(struct _Task* task,char* ouput);
struct _Task* CreateTask(char* elfFile,struct _Args* args);
struct _Args* CreateArgs();

void mushSuffix();

void loadAElf(struct _Task* task);

#endif