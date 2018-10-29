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
    class ProgramASTnode* programnode;
    class BodyASTnode* bodynode;
    class fieldDeclsASTnode* fieldsnode;
    class fieldDeclASTnode* fieldnode;
    class variableASTnode* variablenode;
    class variablesASTnode* variablesnode;
    class methodDeclsASTnode* methodsnode;
}

%type <programnode> program
%type <bodynode> body
%type <fieldsnode> field_decl_star
%type <fieldnode> field_decl
%type <variablesnode> variables
%type <variablenode> variable
%type <methodsnode> method_decl_star

//%destructor { delete $$; } expr

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%token END 0
%token EOL
%token CLSPRG CALLOUT RETURN BREAK CONTINUE IF ELSE FOR EQEQ NE AND OR SCOLON
%token <stringVal> BOOL VOID TYPE ID PMEQUAL RELOP CHAR STRING
%token <integerVal> DECIMAL HEX 

%left OR AND
%left EQEQ NE
%left RELOP
%left '+' '-'
%left '*' '/' '%' 
%nonassoc '!'

%%
program :
	CLSPRG '{' body '}' {$$ = new ProgramASTnode($3); driver.ast.pRoot = $$;}
	;

body :
	field_decl_star method_decl_star {$$ = new BodyASTnode($1,$2);}
	;

field_decl_star :
	{$$ = new fieldDeclsASTnode();}
	| field_decl_star field_decl {$$->push_back($2);}
	;

field_decl :
	TYPE variables SCOLON {$$ = new fieldDeclASTnode(*$1,$2);}
	;

variables : 
	variable {$$ = new variablesASTnode(); $$->push_back($1);}
	| variables ',' variable { $$->push_back($3); }
	;

variable :
	ID {$$ = new variableASTnode("Normal",*$1);}
	| ID '[' DECIMAL ']' {$$ = new variableASTnode("Array",*$1,$3);}
	;

method_decl_star : {}|ID {$$ = new methodDeclsASTnode(*$1);}

%%


void decaf::Parser::error(const Parser::location_type& l,
			    		  const std::string& m)
{
    driver.error(l, m);
}
