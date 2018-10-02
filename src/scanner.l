%{
#include "parser.tab.h"
int lineno = 0;
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
"class Program"		{return CLSPRG;}
"true"|"false"		{return BOOL;}
"void"				{return VOID;}
"int"|"boolean"		{return TYPE;}
"if"				{return IF;}
"else"				{return ELSE;}
"for"				{return FOR;}
"return"			{return RETURN;}
"break"				{return BREAK;}
"continue"			{return CONTINUE;}
"callout"			{return CALLOUT;}
"//".*					{ }
{id}				{return ID;}
{dec}				{return DECIMAL;}
{hex}				{return HEX;}
"="					{return '=';}
"+="|"-="			{return PMEQUAL;}
","					{return ',';}
";"					{return SCOLON;}
"{"					{return '{';}
"}"					{return '}';}
"["					{return '[';}
"]"					{return ']';}
"+"					{return '+';}
"-"					{return '-';}
"*"					{return '*';}
"/"					{return '/';}
"%"					{return '%';}
">"|"<"|">="|"<="  	{return RELOP;}
"=="				{return EQEQ;}
"!="				{return NE;}
"&&"				{return AND;}
"||"				{return OR;}
"!"					{return '!';}
"("					{return '(';}
")"					{return ')';}
[ \t]				{ }
\'{char}\'			{return CHAR;}
\"{str}\" 			{return STRING;}
\n		     		{++lineno;}
.					{ printf("Line No %d: Unrecognized Character\n", lineno); }

%%

