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
{dec}				{return DECIMAL;}
true|false			{return BOOL;}
{hex}				{return HEX;}
{id}				{return ID;}
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

