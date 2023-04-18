%{

#include <stdio.h>
#include "sh.h"

int yylex(void);
void yyerror(char *);

extern char* WorkPath;


%}

%union{
	int			iValue;
	float		fValue;
	char*		sValue;
	char**		strArray;
	struct _Args*		pargs;
	struct _Task*		ptask;
};

%token PIPE
%token INPUT_REDIRECTION
%token OUTPUT_REDIRECTION
%token APPEND_OUTPUT_REDIRECTION

%token CD_INSTRUCTION

%token CURRENT_DIRECTORY
%token PARENT_DIRECTORY

%token <sValue> NAME
%type <sValue> file
%type <sValue> elf

%type <ptask> Task BashTask
%type <pargs> Args


%type <sValue>	subDirectory
%type <sValue> path 

%type <char*> Command  BashCommand

%%

BashCommand
		: Command		{mushSuffix();}
		| BashCommand Command	{mushSuffix();}
		;

Command
		: BashTask '\n'    {loadAElf(rootTask);}
		| CD_INSTRUCTION path '\n'	{changeCWD($2);}
		| CD_INSTRUCTION file '\n'	{changeCWD($2);}
		;

BashTask
		: Task						{$$ = $1;rootTask = $1;}
		| BashTask PIPE Task		{createPipeBetweenTasks($1,$3),$$ = $3;}
		;

Task
	:	Task INPUT_REDIRECTION file		{RedirectInputFile($1,$3);$$ = $1;}
	|	Task OUTPUT_REDIRECTION file	{RedirectOuputFile($1,$3);$$ = $1;}
	|	elf								{$$ = CreateTask($1,NULL);}
	|	elf Args						{$$ = CreateTask($1,$2);}
	;

Args
	:	NAME				{$$ = CreateArgs();appendArgv($$,$1);}
	|	Args NAME			{$$ = $1;appendArgv($$,$2);}
	;

elf
	:	file			{$$ = $1;}
	;

file
	:	path NAME			{pathAppend($1,LEAF,$2);$$ = $1;}		//
	;


path
	:	CURRENT_DIRECTORY		{$$ = createNewPath(CURRENT);}				//./
	|	PARENT_DIRECTORY		{$$ = createNewPath(PARENT);}					//../	
	|	'/'						{$$ = createNewPath(ROOT);}					///
	|	path subDirectory		{pathAppend($1,SUB,$2);$$ = $1;}			//.../next/
	|	path CURRENT_DIRECTORY	{pathAppend($1,CURRENT,NULL);$$ = $1;}			//..././
	|	path PARENT_DIRECTORY	{pathAppend($1,PARENT,NULL);$$ = $1;}			//.../../
	|							{$$ = createNewPath(DEFAULT_BINARY_DIRECTORY);}				//./
	;


subDirectory
	:	NAME '/'		{pathAddSlah($1);$$ = $1;}
	;


%%
void yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
}


