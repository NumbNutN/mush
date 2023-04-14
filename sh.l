%{
#include <stdlib.h>
void yyerror(char *);
#include "sh.tab.h"
%}


%%

[./A-Za-z0-9_]*	{yylval.sValue = (char*)malloc(sizeof(char)*20);strcpy(yylval.sValue,yytext);return NAME;}
"|"				{return PIPE;}
">"				{return OUTPUT_REDIRECTION;}
"<"				{return INPUT_REDIRECTION;}

[\n]			{return '\n';}

[ \t]			{}

%%

int yywrap(void) 
{
	return 1;
}
