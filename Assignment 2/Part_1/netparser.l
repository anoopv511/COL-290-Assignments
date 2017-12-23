%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"



%}
alpha [a-zA-Z_]+

FLOAT [0-9]*\.?[0-9]+  
INTEGER [0-9]+

Value ({INTEGER}|{FLOAT})+("F"|"P"|"K"|"N"|"M"|"MEG")? 

white [ \t]*

%%
"V"({alpha}|{INTEGER})*                               {   printf("V\n" );  yylval.string  =strdup(yytext); return  vol; }
"I"({alpha}|{INTEGER})*                               {      printf("I\n" );    yylval.string  =strdup(yytext); return  isrc; }
((({alpha}+{INTEGER}*)({alpha}|{INTEGER})*)|0)					{ printf("N\n" );yylval.string  =strdup(yytext); return  NAME;}
{Value}                               {    printf("R\n" );yylval.string  =strdup(yytext); return  RESISTOR; }
{Value}"H"                               {  printf("I\n" ); yylval.string  =strdup(yytext);  return  INDUCTOR; }
{Value}"F"                               {     printf("C\n" );  yylval.string  =strdup(yytext);  return  CAPACITOR; }
"SINE"{white}"("{white}{Value}{white}{Value}{white}{Value}{white}"Khz"{white}{Value}{white}"S"{white}{Value}?{white}")"{white}    {  printf("S\n" ); yylval.string  =strdup(yytext); return  SINE;}
\n                                      {         return COMMENT;}
[ \t]                                   {;}
%%
int yywrap(void){
    return 1;
}


