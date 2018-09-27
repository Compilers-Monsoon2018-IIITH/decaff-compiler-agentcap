%{
#include <stdio.h>	
%}

%token DECIMAL BOOL HEX ID RELOP EQEQ NE AND OR CHAR STRING

%start expr

%left OR
%left AND
%left EQEQ NE
%left RELOP
%left '+' '-'
%left '*' '/' '%' 


%%
location : id
	| id '[' expr ']'
	;

expr : 	location
	| literal
	| expr bin_op expr
	| '-' expr
	| '!' expr
	| '(' expr ')'
	;


callout_arg : expr
	| string_literal
	;

bin_op : arith_op
	| rel_op
	| eq_op
	| cond_op
	;

arith_op : '+'
	| '-'
	| '*'
	| '/'
	| '%'
	;

rel_op : RELOP;

eq_op : EQEQ
	| NE
	;

cond_op : AND
	| OR
	;

literal : int_literal
	| char_literal
	| bool_literal
	;

id : ID;

int_literal : decimal_literal
	| hex_literal
	;

decimal_literal : DECIMAL;

hex_literal : HEX;

bool_literal : BOOL;

char_literal :  CHAR;

string_literal : STRING;

%%

main(int argc, char **argv)
{
	yyparse();
	printf("Parsing Over\n");
}

yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}