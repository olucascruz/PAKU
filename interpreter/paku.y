/*
	Interpretador v.1 - Interpreta a linguagem paku
	Lucas Cruz
*/

%{
#define YYSTYPE double
#include <stdio.h>
#include <math.h>
extern FILE* yyin;

void yyerror(char *s);
int yylex(void);
int yyparse();
%}

%token NUMBER EOL
%token PLUS MINUS DIVIDE TIMES
%token P_LEFT P_RIGHT POW MOD ASSIGNMENT PRINT

%left PLUS MINUS
%left TIMES DIVIDE
%left POW MOD
%left P_LEFT P_RIGHT ASSIGNMENT PRINT

%%
%union{
	char[5] string;
	float f;
}

%type <string> STRING:
	STRING PRINT P_LEFT EXPRESSION P_RIGHT EOL{$$ = $1; printf("%s", $1);}
	|
	|
	;

% type <f> STATEMENT:
	STATEMENT EXPRESSION EOL {$$ = $2;}
	|	
	|
	;

% type <f> EXPRESSION: NUMBER {$$ = $1;}
	|	EXPRESSION PLUS EXPRESSION {$$ = $1 + $3;}
	|	EXPRESSION MINUS EXPRESSION {$$ = $1 - $3;}
	|	EXPRESSION TIMES EXPRESSION {$$ = $1 * $3;}
	|	EXPRESSION DIVIDE EXPRESSION {
										if($3 == 0)
											yyerror("division by zero");
										else
											$$ = $1 / $3;
										}
	|	EXPRESSION POW EXPRESSION {$$ = pow($1, $3);}
	|	EXPRESSION MOD EXPRESSION {$$ = fmod($1, $3);}
	|	P_LEFT EXPRESSION P_RIGHT {$$ = $2;}
	|	EXPRESSION ASSIGNMENT EXPRESSION {$$ = $1;}
	;

%%

void yyerror(char *s)
{
	printf("Error: %s\n", s);
}

int main(int argc, char *argv[])
{
	if (argc == 1)
    {
		yyparse();
    }

	if (argc == 2)
	{
    	yyin = fopen(argv[1], "r");
		yyparse();
    }

	return 0;
}
