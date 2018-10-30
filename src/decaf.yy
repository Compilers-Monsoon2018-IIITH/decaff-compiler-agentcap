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
%token <integerVal> INT

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
	| ID '[' INT ']' {$$ = new variableASTnode("Array",*$1,$3);}
	;

method_decl_star :
	{$$ = new methodDeclsASTnode();}
	| method_decl method_decl_star {$$->push_back($1);}
	;

method_decl : 
	VOID ID '(' parameters_list ')' block {$$ = new methodDeclASTnode(*$1,$2,$4,$6);}
	| TYPE ID '(' parameters_list ')' block {$$ = new methodDeclASTnode(*$1,$2,$4,$6);}
	;

block : 
	'{' var_decl_star statement_star '}' {$$ = new blockASTnode($2,$3);}
	;

var_decl_star :
	{$$ = new varDeclsASTnode();}
	| var_decl_star var_decl{$$->push_back($2);}
	;

var_decl :
	TYPE ID_plus SCOLON {$$ = new varDeclASTnode(*$1,$2);}
	;

ID_plus : 
	ID {$$ = new idsASTnode();$$->push_back(*$1);}
	| ID_plus ',' ID {$$->push_back(*$3);}
	;

statement_star :
	{$$ = new stmtsASTnode();}
	| statement_star statement {$$->push_back($2);}
	;

statement : 
	location '=' expr SCOLON {$$ = new stmtASTnode( new assignASTnode($1,'=',$3));}
	| location PMEQUAL expr SCOLON {$$ = new stmtASTnode( new assignASTnode($1,*$2,$3));}
	| method_call SCOLON {$$ = new stmtASTnode($1);}
	| IF '(' expr ')' block {$$ = new stmtASTnode( new ifElseASTnode($3,$5,NULL));}
	| IF '(' expr ')' block ELSE block {$$ = new stmtASTnode( new ifElseASTnode($3,$5,$7));}
	| FOR ID '=' expr ',' expr block {$$ = new stmtASTnode(new forASTnode(*$2,$4,$6,$7));}
	| RETURN SCOLON {$$ = new stmtASTnode(new rtnStmtASTnode(NULL));}
	| RETURN expr SCOLON {$$ = new stmtASTnode(new rtnStmtASTnode($2));}
	| BREAK SCOLON {$$ = new stmtASTnode(new breakStmtASTnode());}
	| CONTINUE SCOLON {$$ = new stmtASTnode(new continueStmtASTnode());}
	| block {$$ = new stmtASTnode(new blockASTnode($1));}
	;

method_call :
	ID '(' ')' { $$ = new methodASTnode(*$1,NULL);}
	| ID '(' expr_list ')' { $$ = new methodASTnode("Default",*$1,$3);}
	| CALLOUT '(' STRING ')' { $$ = new methodASTnode("Callout",*$3,NULL);}
	| CALLOUT '(' STRING ',' callout_arg_plus ')' { $$ = new methodASTnode("Callout",*$3,$5);}
	;

callout_arg_plus : 
	callout_arg {$$ = new callOutArgsASTnode(); $$->push_back($1);}
	| callout_arg_plus ',' callout_arg {$$->push_back($3);}
	;

expr_list : 
	expr {$$ = new exprListASTnode(); $$->push_back($1);}
	| expr_list ',' expr {$$->push_back($3);}
	;

location : 
	ID {$$ = new locationASTnode("Normal",*$1);}
	| ID '[' expr ']' {$$ = new locationASTnode("Array",*$1,$3);}
	;

parameters_list:
	{$$ = new paramListASTnode(NULL);}
	| parameters {$$ = new paramListASTnode($1);}
	;

parameters : 
	TYPE ID {$$ = new parametersASTnode();$$->push_back(new parameterASTnode(*$1,*$2));}
	| parameters ',' TYPE ID {$$->push_back(new parameterASTnode(*$3,*$4));}
	;

expr : 
	location {$$ = new exprASTnode($1);}
	| method_call {$$ = new exprASTnode($1);}
	| literal {$$ = new exprASTnode($1);}
	|expr '+' expr {$$ = new exprASTnode(new binaryASTnode($1,$2,$3));}
	|expr '-' expr {$$ = new exprASTnode(new binaryASTnode($1,$2,$3));}
	|expr '*' expr {$$ = new exprASTnode(new binaryASTnode($1,$2,$3));}
	|expr '/' expr {$$ = new exprASTnode(new binaryASTnode($1,$2,$3));}
	|expr '%' expr {$$ = new exprASTnode(new binaryASTnode($1,$2,$3));}
	|expr RELOP expr {$$ = new exprASTnode(new binaryASTnode($1,*$2,$3));}
	|expr EQEQ expr {$$ = new exprASTnode(new binaryASTnode($1,*$2,$3));}
	|expr NE expr {$$ = new exprASTnode(new binaryASTnode($1,*$2,$3));}
	|expr AND expr {$$ = new exprASTnode(new binaryASTnode($1,*$2,$3));}
	|expr OR expr {$$ = new exprASTnode(new binaryASTnode($1,*$2,$3));}
	| '-' expr {$$ = new exprASTnode(new unaryASTnode($1,$2));}
	| '!' expr {$$ = new exprASTnode(new unaryASTnode($1,$2));}
	| '(' expr ')' {$$ = new exprASTnode(new unaryASTnode($1,$2));}
	;

callout_arg : 
	expr {$$ = new callArgASTnode($1,NULL);}
	| STRING {$$ = new callArgASTnode(NULL,*$1);}
	;

literal : 
	INT {$$ = new literalASTnode("INT",$1);}
	| CHAR {$$ = new literalASTnode("CHAR",*$1);}
	| BOOL {$$ = new literalASTnode("BOOL",*$1);}
	;
%%


void decaf::Parser::error(const Parser::location_type& l,
			    		  const std::string& m)
{
    driver.error(l, m);
}
