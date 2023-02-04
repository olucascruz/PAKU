/*
	Interpretador v.1 - Interpreta a linguagem paku
	Lucas Cruz
*/

%{
#define YYSTYPE double
#include "paku.tab.h" 
#include <stdlib.h>

void yyerror(char *s); 
%}

%%

[0-9]+("."[0-9]+)? 	{ yylval = atof(yytext); return NUMBER; }
[\n]				{ return EOL; }
[+]					{ return PLUS; }
[-]					{ return MINUS; }
[/]					{ return DIVIDE; }
[*]					{ return TIMES; }
[(]					{ return P_LEFT;}
[)]					{ return P_RIGHT;}
[[:space:]]			;
[\^]				{ return POW;}
[\%]				{ return MOD;}
[\=]				{ return ASSIGNMENT;}
['print_str']		{ return PRINT;}


.					{ yyerror("Undefined token\n"); }

%%

int yywrap()
{
	return 1;
}

