/* $Id$ -*- mode: c++ -*- */
/** \file scanner.ll Define the example Flex lexical scanner */

%{ /*** C/C++ Declarations ***/

#include <string>
#include "scanner.h"

/* import the parser's token type into a local typedef */
typedef decaf::Parser::token token;
typedef decaf::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "decafFlexLexer" */
%option prefix="decaf"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

/* no support for include files is planned */
%option yywrap nounput 

/* enables the use of start condition stacks */
%option stack

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
    #define YY_USER_ACTION  yylloc->columns(yyleng);
%}


alpha [a-zA-Z_]
digit [0-9]
dec {digit}({digit})*
hex 0x({digit}|[a-fA-F])+
alpha_num {alpha}|{digit}
id {alpha}({alpha_num})*
char \\n|\\t|\\'|\\\\|\\\"|[^\\"']
str {char}*

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */
%{
    // reset location
    yylloc->step();
%}

"class Program"     {yylval->stringVal = new std::string(yytext,yyleng); return token::CLSPRG;}
"true"|"false"      {yylval->stringVal = new std::string(yytext,yyleng); return token::BOOL;}
"void"              {yylval->stringVal = new std::string(yytext,yyleng); return token::VOID;}
"int"|"boolean"     {yylval->stringVal = new std::string(yytext,yyleng); return token::TYPE;}
"if"                {return token::IF;}
"else"              {return token::ELSE;}
"for"               {return token::FOR;}
"return"            {return token::RETURN;}
"break"             {return token::BREAK;}
"continue"          {return token::CONTINUE;}
"callout"           {return token::CALLOUT;}
{id}                {yylval->stringVal = new std::string(yytext,yyleng); return token::ID;}
{dec}               {yylval->integerVal = atoi(yytext); return token::DECIMAL;}
/* change atoi to atohex */
{hex}               {yylval->integerVal = atoi(yytext); return token::HEX;}
"="                 {return static_cast<token_type>(*yytext);}
"+="|"-="           {yylval->stringVal = new std::string(yytext,yyleng); return token::PMEQUAL;}
","                 {return static_cast<token_type>(*yytext);}
";"                 {return token::SCOLON;}
"{"                 {return static_cast<token_type>(*yytext);}
"}"                 {return static_cast<token_type>(*yytext);}
"["                 {return static_cast<token_type>(*yytext);}
"]"                 {return static_cast<token_type>(*yytext);}
"+"                 {return static_cast<token_type>(*yytext);}
"-"                 {return static_cast<token_type>(*yytext);}
"*"                 {return static_cast<token_type>(*yytext);}
"/"                 {return static_cast<token_type>(*yytext);}
"%"                 {return static_cast<token_type>(*yytext);}
">"|"<"|">="|"<="   {yylval->stringVal = new std::string(yytext,yyleng); return token::RELOP;}
"=="                {return token::EQEQ;}
"!="                {return token::NE;}
"&&"                {return token::AND;}
"||"                {return token::OR;}
"!"                 {return static_cast<token_type>(*yytext);}
"("                 {return static_cast<token_type>(*yytext);}
")"                 {return static_cast<token_type>(*yytext);}
[ \t\r]+            {yylloc->step();}
\'{char}\'          {yylval->stringVal = new std::string(yytext,yyleng); return token::CHAR;}
\"{str}\"           {yylval->stringVal = new std::string(yytext,yyleng); return token::STRING;}
"//".*              {}
\n                  {
                        yylloc->lines(yyleng);
                        yylloc->step();
                        return token::EOL;
                    }
.                   {
                        printf("Line No : Unrecognized Character\n");
                        return static_cast<token_type>(*yytext); 
                    }

%% /*** Additional Code ***/

namespace decaf {

Scanner::Scanner(std::istream* in,
		         std::ostream* out)
: decafFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

}

/* This implementation of DecafFlexLexer::yylex() is required to fill the
 * vtable of the class DecafFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int decafFlexLexer::yylex()
{
    std::cerr << "in decafFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int decafFlexLexer::yywrap()
{
    return 1;
}

