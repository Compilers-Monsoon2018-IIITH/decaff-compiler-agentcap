%{
#include <stdio.h>	
%}

%token DECIMAL BOOL HEX ID RELOP EQEQ NE AND OR CHAR STRING CLSPRG VOID TYPE IF ELSE FOR RETURN BREAK CONTINUE CALLOUT SCOLON PMEQUAL

%start program

%left OR
%left AND
%left EQEQ NE
%left RELOP
%left '+' '-'
%left '*' '/' '%' 


%%
program : CLSPRG '{' body '}';

body : | field_decl_star method_decl_star | method_decl_star ;

field_decl_star : field_decl | field_decl_star field_decl;

field_decl : TYPE variables SCOLON;

variables : variable
	| variables ',' variable
	;

variable : ID
	| ID '[' int_literal ']'
	;

method_decl_star :
	| method_decl | method_decl_star method_decl
	;

method_decl : VOID ID '(' parameters_list ')' block
	| TYPE ID '(' parameters_list ')' block
	;

block : '{' var_decl_star statement_star '}'
	;

var_decl_star :
	| TYPE ID_plus SCOLON | var_decl_star TYPE ID_plus SCOLON
	;

ID_plus : ID
	| ID_plus ',' ID
	;

statement_star :
	| statement | statement_star statement
	;

statement : location assign_op expr SCOLON
	| method_call SCOLON
	| IF '(' expr ')' block
	| IF '(' expr ')' block ELSE block
	| FOR ID '=' expr ',' expr block
	| RETURN SCOLON
	| RETURN expr SCOLON
	| BREAK SCOLON
	| CONTINUE SCOLON
	| block
	;

assign_op : '=' | PMEQUAL;

method_call : method_name '(' ')'
	| method_name '(' expr_list ')'
	| CALLOUT '(' string_literal ')'
	| CALLOUT '(' string_literal ',' callout_arg_plus ')'

callout_arg_plus : callout_arg
	| callout_arg_plus ',' callout_arg
	;

method_name : ID;

expr_list : expr
	| expr_list ',' expr
	;

location : ID
	| ID '[' expr ']'
	;

parameters_list:
	| parameters 
	;

parameters : TYPE ID
	| parameters ',' TYPE ID 
	;

expr : 	location
	| method_call
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

eq_op : EQEQ | NE
	;

cond_op : AND | OR
	;

literal : int_literal
	| char_literal
	| bool_literal
	;

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