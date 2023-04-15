%{
#include <stdlib.h>
void yyerror(char *);
#include "sh.tab.h"
%}


%%
"./"				{return CURRENT_DIRECTORY;}
"../"				{return PARENT_DIRECTORY;}

[.A-Za-z0-9_-]*	{yylval.sValue = (char*)malloc(sizeof(char)*100);strcpy(yylval.sValue,yytext);return NAME;}
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
