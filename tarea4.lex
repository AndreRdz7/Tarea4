%{
#include<stdlib.h>
#include<math.h>
  /* Se incluye el archivo generado por bison para tener las definiciones
     de los tokens */
#include "tarea4.tab.h"
%}

LETRA [A-Za-z]
ENTERO [1-9][0-9]*
DECIMAL {ENTERO}.{ENTERO}
ID [a-zA-Z_][a-zA-Z_0-9]∗

%%

{ENTERO}  {yylval = atoi(yytext); return NUMI;}
{DECIMAL} {yylval = atoi(yytext); return NUMF;}
"program" {return PROGRAM;}
"var"     {return VAR;}
"int"     {return INT;}
"float"   {return FLOAT;}
"set"     {return SET;}
"read"    {return READ;}
"print"   {return PRINT;}
"if"      {return IF;}
"ifelse"  {return IFELSE;}
"while"   {return WHILE;}
"for"     {return FOR;}
"to"      {return TO;}
"step"    {return STEP;}
"do"      {return DO;}
{ID}      {return ID;}
"+"       {return SUMA;}
"-"       {return RESTA;}
"*"       {return MULTI;}
"/"       {return DIVIDE;}
"("       {return PARENI;}
")"       {return PAREND;}
"{"       {return LLAVEI;}
"}"       {return LLAVED;}
":"       {return COLON;}
";"       {return SEMICOLON;}
"<"       {return MENOR;}
">"       {return MAYOR;}
"="       {return IGUAL;}
"<="      {return MENORI;}
">="      {return MAYORI;}
%%
