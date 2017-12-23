%option noyywrap

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	
	char parameters[100];
%}

alpha		[a-zA-Z_]+
integer		[0-9]+
decimal		[0-9]*\.?[0-9]+
space		[ \t]*
val			({integer} | {decimal})("F" | "P" | "K" | "N" | "M" | "MEG")?

%x SIN

%%
<INITIAL>"V"({alpha} | {integer})*				{ yylval.str = strdup(yytext); return VOL;}
<INITIAL>"I"({alpha} | {integer})*				{ yylval.str = strdup(yytext); return CURR;}
<INITIAL>(0 | {alpha}+({integer} | {alpha})*)	{ yylval.str = strdup(yytext); return NAME;}
<INITIAL>{val}"F"								{ yylval.str = strdup(yytext); return CAPACITOR;}
<INITIAL>{val}									{ yylval.str = strdup(yytext); return RESISTOR;}
<INITIAL>{val}"H"								{ yylval.str = strdup(yytext); return INDUCTOR;}
<INITIAL>"SINE"{space}"("{space}				{ BEGIN(SIN);}
<INITIAL>\n 									{ return NEWLINE;}
<INITIAL>[ \t]									{ }
<INITIAL>										{ return SIN;}
<INITIAL>.										{ printf("Invalid Character\n");}

<SIN>{val}										{ strcat(parameters,yytext); strcat(parameters," ");}
<SIN>{space}									{ }
<SIN>")"										{ BEGIN(INITIAL);}
<SIN>"."										{ printf("Invalid Format\n"); return;}
%%