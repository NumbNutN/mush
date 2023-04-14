%{

#include <stdio.h>
#include "sh.h"

int yylex(void);
void yyerror(char *);


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

%token <sValue> NAME
%type <sValue> file
%type <sValue>	elf

%type <ptask> Task BashTask
%type <pargs> Args



%type Command
%type BashCommand

%%

BashCommand
		: Command		{}
		| BashCommand Command	{}
		;

Command
		: BashTask '\n'    {printf("规约为命令\n");loadAElf($1);}
		;

BashTask
		: Task						{printf("规约为批任务");$$ = $1;}
		| BashTask PIPE Task		{$$ = $1;}
		;

Task
	:	Task INPUT_REDIRECTION NAME		{RedirectInputFile($1,$3);$$ = $1;}
	|	Task OUTPUT_REDIRECTION NAME	{RedirectOuputFile($1,$3);$$ = $1;}
	|	elf								{$$ = CreateTask($$,NULL);}
	|	elf Args						{printf("规约为任务");$$ = CreateTask($$,$2);}
	;

Args
	:	NAME				{$$ = CreateArgs($1);}
	|	Args NAME			{appendArgv($1,$2);$$ = $1;}
	;

elf
	:	file			{$$ = $1;printf("规约为elf");}
	;

file
	:	NAME			{$$ = $1;printf("规约为file");}
	;


%%
void yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
}


