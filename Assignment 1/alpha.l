%{
	#include "beta.tab.h"
	void synErr(){
		printf("SynErr\n");
		exit(0);
	}
%}

%%

" + "			{ return ADD; }
" - "			{ return SUB; }
" * "			{ return MUL; }
" / "			{ return DIV; }
[0-9]+		 	{ yylval = atoi(yytext); return NUMBER; }
"SQRT"			{ return SQRT; }
"POW"			{ return POW; }
"LOG"			{ return LOG; }
\n 				{ return EOL; }
[ \t] 			{ }
.				{ synErr(); }

%%
