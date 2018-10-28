%{
#include <stdio.h>	
%}

%token DECIMAL BOOL HEX ID RELOP EQEQ NE AND OR CHAR STRING CLSPRG VOID TYPE IF ELSE FOR RETURN BREAK CONTINUE CALLOUT SCOLON PMEQUAL

%start program

%left OR AND
%left EQEQ NE
%left RELOP
%left '+' '-'
%left '*' '/' '%' 
%left '!'


%%
program :
	CLSPRG '{' body '}'
	;

body :
	field_decl_star method_decl_star
	;

field_decl_star :
	| field_decl_star field_decl
	;

field_decl :
	TYPE variables SCOLON
	;

variables : 
	variable
	| variables ',' variable
	;

variable :
	ID
	| ID '[' int_literal ']'
	;

method_decl_star :
	| method_decl method_decl_star
	;

method_decl : 
	VOID ID '(' parameters_list ')' block
	| TYPE ID '(' parameters_list ')' block
	;

block : 
	'{' var_decl_star statement_star '}'
	;

var_decl_star :
	| var_decl_star TYPE ID_plus SCOLON
	;

ID_plus : ID
	| ID_plus ',' ID
	;

statement_star :
	| statement_star statement
	;

statement : 
	location assign_op expr SCOLON
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


assign_op :
	'=' 
	| PMEQUAL
	;

method_call :
	method_name '(' ')'
	| method_name '(' expr_list ')'
	| CALLOUT '(' STRING ')'
	| CALLOUT '(' STRING ',' callout_arg_plus ')'
	;

callout_arg_plus : 
	callout_arg
	| callout_arg_plus ',' callout_arg
	;

method_name : 
	ID
	;

expr_list : 
	expr
	| expr_list ',' expr
	;

location : 
	ID
	| ID '[' expr ']'
	;

parameters_list:
	| parameters 
	;

parameters : 
	TYPE ID
	| parameters ',' TYPE ID 
	;

expr : 
	location
	| method_call
	| literal
	|expr '+' expr
	|expr '-' expr
	|expr '*' expr
	|expr '/' expr
	|expr '%' expr
	|expr RELOP expr
	|expr EQEQ expr
	|expr NE expr
	|expr AND expr
	|expr OR expr	
	| '-' expr
	| '!' expr
	| '(' expr ')'
	;


callout_arg : 
	expr
	| STRING
	;

literal : 
	int_literal
	| CHAR
	| BOOL
	;

int_literal : 
	DECIMAL
	| HEX
	;

%%

int main(int argc, char **argv)
{
	yyparse();
	printf("Parsing Over\n");
}

int yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}