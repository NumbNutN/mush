%{
#include <stdlib.h>
#include <stdio.h>
void yyerror(char *);
#include "sh.tab.h"
%}


%%

"cd"				{return CD_INSTRUCTION;}
[.A-Za-z0-9_-]*	{yylval.sValue = (char*)malloc(sizeof(char)*100);strcpy(yylval.sValue,yytext);return NAME;}

"./"				{return CURRENT_DIRECTORY;}
"../"				{return PARENT_DIRECTORY;}

"|"				{return PIPE;}
">"				{return OUTPUT_REDIRECTION;}
"<"				{return INPUT_REDIRECTION;}

[\n]			{return '\n';}
[/]				{return '/';}	

[ \t]			{}

%%

int yywrap(void) 
{
	return 1;
}
