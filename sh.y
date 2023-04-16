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

%token CURRENT_DIRECTORY
%token PARENT_DIRECTORY

%token <sValue> NAME
%type <strArray> file
%type <strArray> elf

%type <ptask> Task BashTask
%type <pargs> Args


%type <sValue>	subDirectory
%type <strArray> path 

%type <char*> Command  BashCommand

%%

BashCommand
		: Command		{}
		| BashCommand Command	{}
		;

Command
		: BashTask '\n'    {printf("规约为命令\n");loadAElf($1);}
		;

BashTask
		: Task						{printf("规约为批任务\n");$$ = $1;}
		| BashTask PIPE Task		{$$ = $1;}
		;

Task
	:	Task INPUT_REDIRECTION NAME		{RedirectInputFile($1,$3);$$ = $1;}
	|	Task OUTPUT_REDIRECTION NAME	{RedirectOuputFile($1,$3);$$ = $1;}
	|	elf								{$$ = CreateTask($1,NULL);}
	|	elf Args						{printf("规约为任务\n");$$ = CreateTask($1,$2);}
	;

Args
	:	NAME				{$$ = CreateArgs();appendArgv($$,$1);}
	|	Args NAME			{$$ = $1;appendArgv($$,$2);}
	;

elf
	:	file			{$$ = $1;printf("规约为elf\n");}
	;

file
	:	path NAME			{pathAppend($1,LEAF,$2);$$ = $1;printf("规约为file\n");}		//
	;


path
	:	CURRENT_DIRECTORY		{createNewPath($$,CURRENT);}				//./
	|	PARENT_DIRECTORY		{createNewPath($$,PARENT);}					//../	
	|	'/'						{createNewPath($$,ROOT);}					///
	|	path subDirectory		{pathAppend($1,SUB,$2);$$ = $1;}			//.../next/
	|	path CURRENT_DIRECTORY	{pathAppend($1,CURRENT,NULL);$$ = $1;}			//..././
	|	path PARENT_DIRECTORY	{pathAppend($1,CURRENT,NULL);$$ = $1;}			//.../../
	|
	;


subDirectory
	:	NAME '/'		{$$ = $1;}
	;


%%
void yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
}


