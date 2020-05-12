%{
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h> 
extern int yylex();
extern FILE *yyin;
int yyerror(char const * s);

enum Types {IntType, FloatType}; 

typedef struct Node{
     char name[256];
     enum Types type;
     struct Node * next;
} Node;

int position = 0;
enum Types my_expr_types [256];

void errorRepeatVariableName(char *);
void errorNoId(char *);
void setLinkedListHead();
void printIDs(Node *);
void variableDeclaration(Node , char);
void assignTypeToVariable(Node *,char *);
void checkIfIdExists(Node *,char *);
void checkIfExistsAndAddToExpression(Node *,char *);
void addFloat();
void addInt();
void compareTypes();
void errorType();
const char * getType(enum Types);

Node * head;
Node * actual;

%}


/* Los elementos terminales de la gramatica. La declaracion de abajo se
convierte en definicion de constantes en el archivo tarea4.tab.h
que hay que incluir en el archivo de flex. */

%union{
     char* name;
     char* type;
}


%token <name> ID 

%token <type> INT FLOAT

%token MENOR MAYOR IGUAL NUMI NUMF MULT DIVIDE SUMA RESTA LLAVE_A LLAVE_C WHILE FOR STEP TO DO IF IFELSE SET PRINT READ VAR DOS_PUNTOS PROG PUNTO_COMA OPT_DECLS DECLS DEC TIPO STMT ASSIG_STMT IF_STMT ITER_STMT CMP_STMT STMT_LST EXPR TERM FACTOR EXPRESION FINEXP PROGRAM PARENTESIS_A PARENTESIS_C
%start prog

%%

prog : PROGRAM ID LLAVE_A opt_decls LLAVE_C stmt  {printf("Aceptado\n");};

opt_decls : decls
          | %empty
;

decls : dec PUNTO_COMA decls 
      | dec
;

dec : VAR ID {variableDeclaration(head, yylval.name);} DOS_PUNTOS tipo;

tipo : INT {assignTypeToVariable(actual, yylval.type);}
     | FLOAT {assignTypeToVariable(actual, yylval.type);}
;

stmt : assign_stmt
     | if_stmt
     | iter_stmt
     | cmp_stmt
;

assign_stmt : SET ID {checkIfIdExists(head, yylval.name);} expr {compareTypes();} PUNTO_COMA
           | READ ID {checkIfIdExists(head, yylval.name);} PUNTO_COMA
           | PRINT expr {compareTypes();} PUNTO_COMA
;

if_stmt : IF PARENTESIS_A expresion {compareTypes();} PARENTESIS_C stmt
        | IFELSE PARENTESIS_A expresion {compareTypes();} PARENTESIS_C stmt stmt
;

iter_stmt : WHILE PARENTESIS_A expresion {compareTypes();} PARENTESIS_C stmt
          | FOR SET ID {checkIfIdExists(head, yylval.name);} expr {compareTypes();} TO expr {compareTypes();} STEP expr {compareTypes();} DO stmt
;

cmp_stmt : LLAVE_A LLAVE_C
         | LLAVE_A stmt_lst LLAVE_C
;

stmt_lst : stmt
         | stmt_lst stmt
;

expr : expr SUMA term
     | expr RESTA term
     | term
;

term : term MULT factor
     | term DIVIDE factor
     | factor
;

factor : PARENTESIS_A expr {compareTypes();} PARENTESIS_C
       | ID {checkIfExistsAndAddToExpression(head, yylval.name);}
       | NUMI { addInt();  }
       | NUMF { addFloat(); }
;

expresion : expr MENOR expr
          | expr MAYOR expr
          | expr IGUAL expr
          | expr MENOR IGUAL expr
          | expr MAYOR IGUAL expr
;

%%

int yyerror(char const * s) {
     fprintf(stderr, "%s\n", s);
}

const char* getType(enum Types type) 
{
     switch (type) 
     {
          case IntType: return "int";
          case FloatType: return "float";
     }
}

void errorNoId(char * name){
     printf("La variable %s nunca fue declarada\n",name);
     exit(0);
}

void errorRepeatVariableName(char * name){
     printf("La variable %s ya habia sido declarada\n",name);
     exit(0);
}

void errorType(){
     printf("Se intento una operacion entre variables de distinto tipo\n");
     exit(0);
}

void checkIfExistsAndAddToExpression(Node * head,char * nameId){
      //creo nuevo nodo para recorrer y checar si existe
     Node * current = head;
     //printf("Intengo ver id de expr, el id es: %s\n", nameId);

     while(current->next != NULL){
          current = current->next;

          if (strcmp(current->name, nameId) == 0){
               my_expr_types[position] = current->type;
               //printf("Agrego Tipo: %s\n", getType(current->type));
               position++;
          }
     }
}

void addFloat(){
     my_expr_types[position] = FloatType;
     position++;
}

void addInt(){
     my_expr_types[position] = IntType;
     position++;
}

void compareTypes(){
     enum Types firstone = my_expr_types[0];
     //printf("Mi primer tipo es: %s\n", getType(firstone));

     if(position > 1){
          for(int i = 1; i <= position; i++){
               if(my_expr_types[i] != firstone){
                    errorType();
               }
          }
     }

     //reset it
     //printf("reset: %d\n", position);
     memset(my_expr_types, NULL, sizeof(my_expr_types));
     position = 0;
}

void checkIfIdExists(Node * head, char * nameId){
      //creo nuevo nodo para recorrer y checar si existe
     Node * current = head;
     bool exists = false;

     while(current->next != NULL){
          current = current->next;

          if (strcmp(current->name, nameId) == 0){
               exists = true;
          }
     }

     // si existe, continua :D, sino error
     if(exists == false){
          errorNoId(nameId);
     }
     //printf("Si existe :D\n");
}

void setLinkedListHead(){
     head = (Node*)malloc(sizeof(Node));
     strcpy(head->name, "_INIT_");
     head->next = NULL;

     actual = head;
}

void printIDs(Node * actualId){
     if(actualId != NULL){
          printf("ID: '%s' of type: %s\n", actualId->name, getType(actualId->type));
          printIDs(actualId->next);
     }
}

void assignTypeToVariable(Node * actual, char * type){
     //printf("ID actual: %s, asignando tipo: %s", actual->name, type);

     if (strcmp(type, "int") == 0){
          actual->type = IntType;
     }else{
          actual->type = FloatType;
     }
}

void variableDeclaration(Node * head, char * name){
     //creo nuevo nodo para recorrer y checar si existe
     Node * current = head;
     //printf("Agrego nuevo id: %s\n", name);     
     while(current->next != NULL){
          current = current->next;

          if (strcmp(current->name, name) == 0){
               errorRepeatVariableName(name);
          }
     }

     Node * newNode = (Node*)malloc(sizeof(Node));
     current->next = newNode;
     strcpy(newNode->name, name);
     actual = newNode;
}

int main(int argc, char *argv[]) {
     // Checking if there is an argument

     printf("Bison, syntatic parser:\n");

     if (argc < 2 || argc > 2)  
     { 
          printf("enter 1 argument only eg.\"filename!\"\n"); 
          return 0; 
     } 

     char * file_name = argv[1];  
     FILE * fp  = fopen(file_name, "r"); // read only 

	// check if file exists
	if (fp == NULL) 
	{   
		printf("Error! Could not open file\n"); 
		return 0;
	} 

     yyin = fp; 

     setLinkedListHead();
     yyparse();
     printf("List of IDs:\n");
     printIDs(head->next);
}