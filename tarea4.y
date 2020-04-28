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
           | PRINT expr SEMICOLON {printf("%d\n", $1);}
;

if_stmt : IF PARENI expresion PAREND stmt {if($3 == 1)$5;}
        | IFELSE PARENI expresion PAREND stmt stmt {if($3 == 1)$5;$6;}
;

iter_stmt : WHILE PARENI expresion PAREND stmt {while($3)$5;}
          | FOR SET ID expr TO expr STEP expr DO stmt {for($4;$6;$8)$10;}
;

cmp_stmt : LLAVEI LLAVED
         | LLAVEI stmt_lst LLAVED
;

stmt_lst : stmt
         | stmt_lst stmt
;

expr : expr SUMA term {$$ = $1 + $3;}
     | expr RESTA term {$$ = $1 - $3;}
     | term
;

term : term MULTI factor {$$ = $1 * $3;}
     | term DIVIDE factor {$$ = $1 / $3;}
     | factor
;

factor : PARENI expr PAREND {$$ = $2;}
       | ID
       | NUMI
       | NUMF
;

expresion : expr MENOR expr {if($1 < $3){return 1;}}
          | expr MAYOR expr {if($1 > $3){return 1;}}
          | expr IGUAL expr {if($1 == $3){return 1;}}
          | expr MENORI expr {if($1 <= $3){return 1;}}
          | expr MAYORI expr {if($1 >= $3){return 1;}}
;

%%

int yyerror(char const * s) {
  fprintf(stderr, "%s\n", s);
}

void main() {
  yyparse();
}

