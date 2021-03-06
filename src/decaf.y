%{
#include "PostFixVisitor.h"
#include "CodeGenerator.h"
#include "ast.h"
#include <bits/stdc++.h>

  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern "C" int line_num;
  extern union Node yylval;
  void yyerror(const char *s);
  class ProgramASTnode* start = NULL;
  int errors=0;
%}

/* -------------	Tokens 		------------- */
%start program

%token END 0
%token EOL
%token CLSPRG CALLOUT RETURN BREAK CONTINUE IF ELSE FOR SCOLON
%token <stringVal> BOOL VOID TYPE ID PMEQUAL RELOP CHAR STRING EQEQ NE AND OR
%token <integerVal> INT


/* %define parse.error verbose */
%left OR AND
%left EQEQ NE
%left RELOP
%left '+' '-'
%left '*' '/' '%' 
%nonassoc '!'

%type <programnode> program
%type <bodynode> body
%type <fielddeclsnode> field_decl_star
%type <fielddeclnode> field_decl
%type <variablesnode> variables
%type <variablenode> variable
%type <methoddeclsnode> method_decl_star
%type <methoddeclnode> method_decl
%type <blocknode> block
%type <vardeclsnode> var_decl_star
%type <vardeclnode> var_decl
%type <idsnode> ID_plus
%type <stmtsnode> statement_star
%type <stmtnode> statement
%type <methodcallnode> method_call
%type <calloutargsnode> callout_arg_plus
%type <exprlistnode> expr_list
%type <locationnode> location
%type <paramlistnode> parameters_list
%type <parametersnode> parameters
%type <exprnode> expr
%type <callargnode> callout_arg
%type <literalnode> literal
/* -------------	Grammer Rules		------------- */
%%
program :
	CLSPRG '{' body '}' {$$ = new ProgramASTnode($3); start = $$;}
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
	| variables ',' variable { $$=$1;$$->push_back($3); }
	;

variable :
	ID {$$ = new variableASTnode("Normal",*$1);}
	| ID '[' INT ']' {$$ = new variableASTnode("Array",*$1,$3);}
	;

method_decl_star :
	{$$ = new methodDeclsASTnode();}
	| method_decl method_decl_star {$2->push_back($1); $$=$2;}
	;

method_decl : 
	VOID ID '(' parameters_list ')' block {$$ = new methodDeclASTnode(*$1,*$2,$4,$6);}
	| TYPE ID '(' parameters_list ')' block {$$ = new methodDeclASTnode(*$1,*$2,$4,$6);}
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
	| ID_plus ',' ID {$1->push_back(*$3); $$=$1;}
	;

statement_star :
	{$$ = new stmtsASTnode();}
	| statement_star statement {$1->push_back($2);  $$=$1;}
	;

statement : 
	location '=' expr SCOLON {$$ = new stmtASTnode( new assignASTnode($1,"=",$3));}
	| location PMEQUAL expr SCOLON {$$ = new stmtASTnode( new assignASTnode($1,*$2,$3));}
	| method_call SCOLON {$$ = new stmtASTnode($1);}
	| IF '(' expr ')' block {$$ = new stmtASTnode( new ifElseASTnode($3,$5,NULL));}
	| IF '(' expr ')' block ELSE block {$$ = new stmtASTnode( new ifElseASTnode($3,$5,$7));}
	| FOR ID '=' expr ',' expr block {$$ = new stmtASTnode(new forASTnode(*$2,$4,$6,$7));}
	| RETURN SCOLON {$$ = new stmtASTnode(new rtnStmtASTnode(NULL));}
	| RETURN expr SCOLON {$$ = new stmtASTnode(new rtnStmtASTnode($2));}
	| BREAK SCOLON {$$ = new stmtASTnode(new breakStmtASTnode());}
	| CONTINUE SCOLON {$$ = new stmtASTnode(new continueStmtASTnode());}
	| block {$$ = new stmtASTnode($1);}
	;

method_call :
	ID '(' ')' { $$ = new methodCallASTnode("Default",*$1,NULL);}
	| ID '(' expr_list ')' { $$ = new methodCallASTnode("Default",*$1,$3);}
	| CALLOUT '(' STRING ')' { $$ = new methodCallASTnode("Callout",*$3,NULL);}
	| CALLOUT '(' STRING ',' callout_arg_plus ')' { $$ = new methodCallASTnode("Callout",*$3,$5);}
	;

callout_arg_plus : 
	callout_arg {$$ = new callOutArgsASTnode(); $$->push_back($1);}
	| callout_arg_plus ',' callout_arg {$1->push_back($3); $$=$1;}
	;

expr_list : 
	expr {$$ = new exprListASTnode(); $$->push_back($1);}
	| expr_list ',' expr {$1->push_back($3); $$=$1;}
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
	| parameters ',' TYPE ID {$1->push_back(new parameterASTnode(*$3,*$4)); $$=$1;}
	;

expr : 
	location {$$ = new exprASTnode($1);}
	| method_call {$$ = new exprASTnode($1);}
	| literal {$$ = new exprASTnode($1);}
	|expr '+' expr {$$ = new exprASTnode(new binaryASTnode($1,"+",$3));}
	|expr '-' expr {$$ = new exprASTnode(new binaryASTnode($1,"-",$3));}
	|expr '*' expr {$$ = new exprASTnode(new binaryASTnode($1,"*",$3));}
	|expr '/' expr {$$ = new exprASTnode(new binaryASTnode($1,"/",$3));}
	|expr '%' expr {$$ = new exprASTnode(new binaryASTnode($1,"%",$3));}
	|expr RELOP expr {$$ = new exprASTnode(new binaryASTnode($1,*$2,$3));}
	|expr EQEQ expr {$$ = new exprASTnode(new binaryASTnode($1,"==",$3));}
	|expr NE expr {$$ = new exprASTnode(new binaryASTnode($1,"!=",$3));}
	|expr AND expr {$$ = new exprASTnode(new binaryASTnode($1,"&&",$3));}
	|expr OR expr {$$ = new exprASTnode(new binaryASTnode($1,"||",$3));}
	| '-' expr {$$ = new exprASTnode(new unaryASTnode("-",$2));}
	| '!' expr {$$ = new exprASTnode(new unaryASTnode("!",$2));}
	| '(' expr ')' {$$ = $2;}
	;

callout_arg : 
	expr {$$ = new callArgASTnode($1,"");}
	| STRING {$$ = new callArgASTnode(NULL,*$1);}
	;

literal : 
	INT {$$ = new literalASTnode("INT",$1);}
	| CHAR {$$ = new literalASTnode("CHAR",*$1);}
	| BOOL {$$ = new literalASTnode("BOOL",*$1);}
	;

%%
int main(int argc, char **argv) {
  	if(argc == 1) {
		printf("No Input File Given\n");
		exit(-1);
	}

	FILE *input = fopen(argv[1], "r");

	if (input == NULL){
		printf("Unable to open the given file!\n");
		exit(-1);
	}
	yyin = input;
	yyparse();

	PostFixVisitor pfv;
	//pfv.visit(*start);

	CodeGen cgn;
	map<string,llvm::AllocaInst *> Old_vals;
	cgn.codegen(*start,Old_vals);
	start->printCode();
}

void yyerror(const char *s){
	errors++;
	printf("Error:%s at %d\n",s,line_num);
  exit(-1);
}
