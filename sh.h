#ifndef _SH_H
#define _SH_H

#include <stdint.h>

typedef struct _Args{
    int argc;
    char** argv;
} Args,*pArgs;

typedef struct _Task{

    char* elfName;
    struct _Args args;
    char* inputFile;
    char* outputFile;
    struct _Task* nextTask;
    unsigned char pipeExit;

}Task,*pTask;


enum _Path{
    PARENT,
    CURRENT,
    ROOT,
    SUB,
    LEAF,
    DEFAULT_BINARY_DIRECTORY
};

extern struct _Task* rootTask;

extern char* CurrentWorkDirectory;

void appendArgv(struct _Args* args,char* new_arg);
void RedirectInputFile(struct _Task* task,char* input);
void RedirectOuputFile(struct _Task* task,char* ouput);
struct _Task* CreateTask(char* elfFile,struct _Args* args);
struct _Args* CreateArgs();

void mushSuffix();

void loadAElf(struct _Task* task);

char* createNewPath(enum _Path type);
void pathAppend(char* oriPath,enum _Path type,char* subPath);
void pathPopSubDirectory(char* oriPath);
void pathAppendSubDirectory(char** oriPath,char* appendPath);
void pathAddSlah(char* path);


/**********************/
/*        FILE        */
/**********************/

//#define STANDARD_INPUT_FILE "/proc/sekf/fd/0"
//#define STANDARD_OUTPUT_FILE    "/proc/sekf/fd/1"
//#define STANDARD_ERROR_FILE "/proc/sekf/fd/2"
#define STANDARD_INPUT_FILE "/dev/stdin"
#define STANDARD_OUTPUT_FILE "/dev/stdout"
#define STANDARD_ERROR_FILE "/dev/stderr"

#define DEFAULT_MUSH_PIPE "/tmp/mush_pipe"

void createPipeBetweenTasks(struct _Task* outputTask,struct _Task* InputTask);
void closePipe();

void changeCWD(char* newCWD);

#endif