%{

#include <bits/stdc++.h>
#include "ast.h"
#include "decaf.tab.h"
#define YY_DECL extern "C" int yylex()
	extern union Node yylval;
	using namespace std;
	int line_num = 0;
%}

alpha [a-zA-Z_]
digit [0-9]
dec {digit}({digit})*
hex 0x({digit}|[a-fA-F])+
alpha_num {alpha}|{digit}
id {alpha}({alpha_num})*
char \\n|\\t|\\'|\\\\|\\\"|[^\\"']
str {char}*

%%

"class Program"     {return CLSPRG;}
"true"|"false"      {yylval.stringVal = new std::string(yytext,yyleng); return BOOL;}
"void"              {yylval.stringVal = new std::string(yytext,yyleng); return VOID;}
"int"|"boolean"     {yylval.stringVal = new std::string(yytext,yyleng); return TYPE;}
"if"                {return IF;}
"else"              {return ELSE;}
"for"               {return FOR;}
"return"            {return RETURN;}
"break"             {return BREAK;}
"continue"          {return CONTINUE;}
"callout"           {return CALLOUT;}
{id}                {yylval.stringVal = new std::string(yytext,yyleng); return ID;}
{dec}               {yylval.integerVal = atoi(yytext); return INT;}
{hex}               {yylval.integerVal = atoi(yytext); return INT;}
"="                 {return '=';}
"+="|"-="           {yylval.stringVal = new std::string(yytext,yyleng); return PMEQUAL;}
","                 {return ',';}
";"                 {return SCOLON;}
"{"                 {return '{';}
"}"                 {return '}';}
"["                 {return '[';}
"]"                 {return ']';}
"+"                 {return '+';}
"-"                 {return '-';}
"*"                 {return '*';}
"/"                 {return '/';}
"%"                 {return '%';}
">"|"<"|">="|"<="   {yylval.stringVal = new std::string(yytext,yyleng); return RELOP;}
"=="                {return EQEQ;}
"!="                {return NE;}
"&&"                {return AND;}
"||"                {return OR;}
"!"                 {return '!';}
"("                 {return '(';}
")"                 {return ')';}
[ \t\r]+            {}
\'{char}\'          {yylval.stringVal = new std::string(yytext,yyleng); return CHAR;}
\"{str}\"           {yylval.stringVal = new std::string(yytext,yyleng); return STRING;}
"//".*              {}
\n                  {
                        line_num++;
                    }
.                   {
                        printf("Line No : %d Unrecognized Character\n",line_num); 
                    }
%%
