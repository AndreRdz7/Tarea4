%{
#include<stdlib.h>
#include<math.h>
  /* Se incluye el archivo generado por bison para tener las definiciones
     de los tokens */
#include "tarea5.tab.h"
%}

LETRA [A-Za-z]
DIGITO [0-9]
ENTERO ("-"|"")({DIGITO})({DIGITO})*
DECIMAL ("-"|"")({DIGITO})({DIGITO})*(".")({DIGITO})({DIGITO})*
ID   ({LETRA}|("_"|"$"){LETRA})({LETRA}|{DIGITO}|"_"|"$")*

%%

{ENTERO}  {yylval.i = atoi(yytext); return NUMI;}
{DECIMAL} {yylval.f = atof(yytext); return NUMF;}
","       {yylval.terminal = yytext; return COMMA;}
"fun"     {yylval.terminal = yytext; return FUN;}
"return"     {yylval.terminal = yytext; return RETURN;}
"program" {yylval.terminal = yytext; return PROGRAM;}
"var"     {yylval.terminal = yytext; return VAR;}
"int"     {yylval.type = yytext; return INT;}
"float"   {yylval.type = yytext; return FLOAT;}
"set"     {yylval.terminal = yytext; return SET;}
"read"    {yylval.terminal = yytext; return READ;}
"print"   {yylval.terminal = yytext; return PRINT;}
"if"      {yylval.terminal = yytext; return IF;}
"ifelse"  {yylval.terminal = yytext; return IFELSE;}
"while"   {yylval.terminal = yytext; return WHILE;}
"for"     {yylval.terminal = yytext; return FOR;}
"to"      {yylval.terminal = yytext; return TO;}
"step"    {yylval.terminal = yytext; return STEP;}
"do"      {yylval.terminal = yytext; return DO;}
{ID}      {yylval.stringValue = yytext; return ID;}
"+"       {yylval.terminal = yytext; return SUMA;}
"-"       {yylval.terminal = yytext; return RESTA;}
"*"       {yylval.terminal = yytext; return MULTI;}
"/"       {yylval.terminal = yytext; return DIVIDE;}
"("       {yylval.terminal = yytext; return PARENI;}
")"       {yylval.terminal = yytext; return PAREND;}
"{"       {yylval.terminal = yytext; return LLAVEI;}
"}"       {yylval.terminal = yytext; return LLAVED;}
":"       {yylval.terminal = yytext; return COLON;}
";"       {yylval.terminal = yytext; return SEMICOLON;}
"<"       {yylval.terminal = yytext; return MENOR;}
">"       {yylval.terminal = yytext; return MAYOR;}
"="       {yylval.terminal = yytext; return IGUAL;}
"<="      {yylval.terminal = yytext; return MENORI;}
">="      {yylval.terminal = yytext; return MAYORI;}
%%

