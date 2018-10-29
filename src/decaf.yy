/* $Id$ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include "ast.h"
#include "scanner.h"
#include "driver.h"

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start program

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix="decaf"

/* set the parser's class identifier */
%define "parser_class_name" "Parser"

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

/*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/

%union
{
	int integerVal;
	std::string* stringVal;
    class ASTnode* astnode;
}

%type <astnode>	line expr stmt


//%destructor { delete $$; } expr

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}


%token DECIMAL BOOL HEX ID RELOP EQEQ NE AND OR CHAR STRING CLSPRG VOID TYPE IF ELSE FOR RETURN BREAK CONTINUE CALLOUT SCOLON PMEQUAL

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

ID_plus : 
	ID
	| ID_plus ',' ID
	;

statement_star :
	| statement_star statement
	;

statement : 
	location '=' expr SCOLON
	| location PMEQUAL expr SCOLON
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

method_call :
	ID '(' ')'
	| ID '(' expr_list ')'
	| CALLOUT '(' STRING ')'
	| CALLOUT '(' STRING ',' callout_arg_plus ')'
	;

callout_arg_plus : 
	callout_arg
	| callout_arg_plus ',' callout_arg
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


void decaf::Parser::error(const Parser::location_type& l,
			    		  const std::string& m)
{
    driver.error(l, m);
}
