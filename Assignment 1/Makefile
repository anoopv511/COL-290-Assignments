calc: alpha.l beta.y
	bison -d beta.y
	flex alpha.l
	gcc -o bignumcalc beta.tab.c lex.yy.c -lfl