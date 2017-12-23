%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"



%}
alpha [a-zA-Z_%&*]+

FLOAT [0-9]*\.?[0-9]+  
INTEGER [0-9]+

Value ({INTEGER}|{FLOAT})+("F"|"P"|"K"|"N"|"M"|"U"|"MEG")? 

white [ \t]*

%s sinestate

%%
<INITIAL>"SINE"									{   yylval.string  =strdup(yytext); BEGIN INITIAL;return  SINE;}
<INITIAL>"V"({alpha}|{INTEGER})*                               {   yylval.string  =strdup(yytext); BEGIN INITIAL;return  vol; }
<INITIAL>"I"({alpha}|{INTEGER})*                               {     yylval.string  =strdup(yytext);  BEGIN INITIAL;return  isrc;}
<INITIAL>((({alpha}+{INTEGER}*)({alpha}|{INTEGER})*)|0)					{ yylval.string  =strdup(yytext); BEGIN INITIAL;return  NAME;}
<INITIAL>{Value}"F"                               {   yylval.string  =strdup(yytext); BEGIN INITIAL; return  CAPACITOR; }
<INITIAL>{Value}                               {    yylval.string  =strdup(yytext);  BEGIN INITIAL;return  RESISTOR;}
<INITIAL>{Value}"H"                               {  yylval.string  =strdup(yytext);  BEGIN INITIAL; return  INDUCTOR;}
<INITIAL>"("										{   yylval.string  =strdup(yytext); BEGIN sinestate;return  LP;}
<sinestate>{Value}								{    yylval.string  =strdup(yytext); BEGIN sinestate;return  RESISTOR; }
<sinestate>{Value}"hz"										{ yylval.string  =strdup(yytext); BEGIN sinestate;return  FREQ;}
<sinestate>{Value}"S"										{ yylval.string  =strdup(yytext); BEGIN  sinestate;return  TIME;}
<sinestate>")"										{  yylval.string  =strdup(yytext); BEGIN INITIAL;return  RP;}
\n                                      {         return COMMENT;}
[ \t]                                   {;}

%%
int yywrap(void){
    return 1;
}


