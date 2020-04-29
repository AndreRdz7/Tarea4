/* 
     Tarea 4
     Implementación de tabla de símbolos y revision de tipo de datos correspondiente
*/

%{

#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>
 
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

union data {
  int i;
  float f;
};

typedef struct Node{
  char name[256];
  char type;
  union data val;
  struct Node *next;
} node_t;

void printList(node_t *head){
  node_t *current = head;
  printf("Tabla de símbolos:\n");
  while(current != NULL){
    if(current->type == 'i'){
      printf("%s: %d\n",current->name, current->val.i);
      current = current->next;
    }else{
      printf("%s: %f\n", current->name, current->val.f);
      current = current->next;
    }
  }
}

void raiseDuplicateVar(char *name){
  printf("La variable %s ya ha sido declarada\n",name);
  exit(0);
}

void raiseInvalidType(char *name){
  printf("La variable %s tiene otro tipo de dato\n",name);
  exit(0);
}

void raiseNoExistingVar(char *name){
  printf("La variable %s no ha sido declarada\n",name);
  exit(0);
}

void push(node_t *head, char *name, char type){
  node_t *current = head;
  while(current->next != NULL){
    if(strcmp(current->name, name) == 0){
      raiseDuplicateVar(name);
    }
    current = current->next;
  }
  current->next = (node_t*)malloc(sizeof(node_t));
  current->next->type = type;
  strcpy(current->next->name, name);
  current->next->next = NULL;
}

void setInt(node_t *head, char *name, int val){
  node_t *current = head;
  while(current->next != NULL){
    if(strcmp(current->name,name) == 0){
      if(current->type == 'i'){
        current->val.i = val;
        return;
      }
      else{
        raiseInvalidType(name);
      }
    }
    current = current->next;
  }
  raiseNoExistingVar(name);
}

void setFloat(node_t *head, char *name, float val){
  node_t *current = head;
  while(current->next != NULL){
    if(strcmp(current->name,name) == 0){
      if(current->type == 'f'){
        current->val.f = val;
        return;
      }
      else{
        raiseInvalidType(name);
      }
    }
    current = current->next;
  }
  raiseNoExistingVar(name);
}

void main() {
  node_t *symbol = NULL;
  symbol = (node_t*)malloc(sizeof(node_t));
  yyparse();
  printList(symbol);
}

