/* 
     Tarea 4
     Implementación de tabla de símbolos y revision de tipo de datos correspondiente
*/

%{
#include<stdio.h>
#include<math.h>
extern int yylex();
int yyerror(char const * s);
%}

%token NUMI NUMF PROGRAM VAR INT FLOAT SET READ PRINT IF IFELSE
WHILE FOR TO STEP DO ID SUMA RESTA DIVIDE MULTI PAREND PARENI 
LLAVED LLAVEI COLON SEMICOLON MENOR MAYOR IGUAL MENORI MAYORI EPSILON

%start prog

%%

prog : PROGRAM ID LLAVEI opt_decls LLAVED stmt 
;

opt_decls : decls 
          | EPSILON 
;

decls : dec SEMICOLON decls 
      | dec
;

dec : VAR ID COLON tipo 
;

tipo : INT
     | FLOAT
;

stmt : assig_stmt
     | if_stmt
     | iter_stmt
     | cmp_stmt
;

assig_stmt : SET ID expr SEMICOLON
           | READ ID SEMICOLON
           | PRINT expr SEMICOLON
;

if_stmt : IF PARENI expresion PAREND stmt
        | IFELSE PARENI expresion PAREND stmt stmt
;

iter_stmt : WHILE PARENI expresion PAREND stmt
          | FOR SET ID expr TO expr STEP expr DO stmt
;

cmp_stmt : LLAVEI LLAVED
         | LLAVEI stmt_lst LLAVED
;

stmt_lst : stmt
         | stmt_lst stmt
;

expr : expr SUMA term
     | expr RESTA term
     | term
;

term : term MULTI factor
     | term DIVIDE factor
     | factor
;

factor : PARENI expr PAREND
       | ID
       | NUMI
       | NUMF
;

expresion : expr MENOR expr
          | expr MAYOR expr
          | expr IGUAL expr
          | expr MENORI expr
          | expr MAYORI expr
;

%%

int yyerror(char const * s) {
  fprintf(stderr, "%s\n", s);
}

void main() {
  yyparse();
}

