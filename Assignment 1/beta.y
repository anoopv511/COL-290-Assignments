%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror(char *s);
%}


%token NUMBER
%token ADD SUB MUL DIV
%token SQRT POW LOG
%token EOL

%%

calclist: 
| calclist exp EOL 	{ printf("= %d\n", $2); }
;

exp: factor
| exp ADD factor 	{ $$ = $1 + $3; }
| exp SUB factor 	{ $$ = $1 - $3; }
;

factor: term
| factor MUL term 	{ $$ = $1 * $3; }
| factor DIV term 	{ $$ = $1 / $3; }
;

term: NUMBER
;

%%

void main(int argc, char **argv){
	yyparse();
}

int yyerror(char *s){
	printf("SynErr\n");
	exit(0);
}