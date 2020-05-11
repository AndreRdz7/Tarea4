/* 
  Tarea 4
  Implementación de tabla de símbolos y revision de tipo de datos correspondiente
*/

%{

/*
1 - Equal
0 - Different
*/
#define strong_helper(T1, T2) _Generic(( (T1){0} ), T2: 1, default: 0 )
#define compare_types_strong(T1, T2) (strong_helper(T1,T2) && strong_helper(T2,T1))

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>
#include <assert.h>

extern int yylex();
int yyerror(char const * s);

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

void setTable();
void declareVariable(node_t*, char*);
void addTypeToVariable(node_t*, char);
void printList(node_t*);
void raiseDuplicateVar(char* name);
void raiseInvalidType(char* name);
void raiseNoExistingVar(char* name);
void raiseInvalidCompatibleTypes();

node_t* symbol = NULL;

%}

%union{
  char* stringValue;
  int intValue;
  float floatValue;
  int var_type;
}
%token <int> NUMI "integer"
%token <float> NUMF "float"
%token <char const *> ID "identifier"

%token  PROGRAM VAR INT FLOAT SET READ PRINT IF IFELSE
WHILE FOR TO STEP DO SUMA RESTA DIVIDE MULTI PAREND PARENI 
LLAVED LLAVEI COLON SEMICOLON MENOR MAYOR IGUAL MENORI MAYORI

%type <var_type> tipo INT FLOAT
%start prog

%%

prog : PROGRAM ID LLAVEI opt_decls LLAVED stmt 
;

opt_decls : decls 
          | %empty 
;

decls : dec SEMICOLON decls 
      | dec
;

dec : VAR ID {declareVariable(symbol, yylval.stringValue);} COLON tipo 
;

tipo : INT {addTypeToVariable(symbol,'i');}
     | FLOAT {addTypeToVariable(symbol, 'f');}
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

void setTable(){
  symbol = (node_t*)malloc(sizeof(node_t));
  strcpy(symbol->name, "__init__");
  symbol->next = NULL;
}

void printList(node_t *head){
  node_t *current = head->next;
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

void raiseInvalidCompatibleTypes(){
  printf("Las variables tienen distintos tipos de dato y no pueden ser utilizarse en la misma operación\n");
  exit(0);
}

void raiseNoExistingVar(char *name){
  printf("La variable %s no ha sido declarada\n",name);
  exit(0);
}

void declareVariable(node_t *head, char *name){
  node_t *current = head;
  while(current->next != NULL){
    if(strcmp(current->name, name) == 0){
      raiseDuplicateVar(name);
    }
    current = current->next;
  }
  current->next = (node_t*)malloc(sizeof(node_t));
  strcpy(current->next->name, name);
  current->next->next = NULL;
}

void addTypeToVariable(node_t *head, char type){
  node_t *current = head;
  while(current->next != NULL){
    current = current->next;
  }
  current->type = type;
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
  /*
  int x,xx;
  float y;
  printf("%d\n", compare_types_strong(typeof(x),typeof(xx)));
  printf("%d\n", compare_types_strong(typeof(x),typeof(y)));
  */
  setTable();
  yyparse();
  printList(symbol->next);
}

