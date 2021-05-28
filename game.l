%option noyywrap
 
%{
#include <stdio.h>
#include <string.h>
#define YY_DECL int yylex()
#include "game.tab.h"
%}
 
%%

[ \t]+	; //whitespaces
\n 		{return NEWLINE;}


"ADD"	{yylval.val = 0; return OPERATION;} //keywords
"SUBTRACT"	{yylval.val = 1; return OPERATION;}
"MULTIPLY"	{yylval.val = 2; return OPERATION;}
"DIVIDE"	{yylval.val = 3; return OPERATION;}
"LEFT"	{yylval.val = 0; return DIRECTION;}
"RIGHT" {yylval.val = 1; return DIRECTION;}
"UP"	{yylval.val = 2; return DIRECTION;}
"DOWN" {yylval.val = 3; return DIRECTION;}
"ASSIGN" {return ASSIGN;}
"TO" {return TO;}
"VALUE" {return VALUE;}
"IN" {return IN;}
"IS" {return IS;}
"VAR" {return VAR;}


\, {return COMMA;} //Special Characters in command
\. {return END;}

[0-9]+ {yylval.val = atoi(yytext); return NUMBER;} //number, variable name, and remaining combinations
[a-zA-Z]+ {strcpy(yylval.text,yytext); return VARIABLE;}
[^ \t\n\,\.]+  {return OTHER;} //Rest of the cases.
%%
 
 