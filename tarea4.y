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
#include <stdbool.h> 

extern int yylex();
extern FILE *yyin;
int yyerror(char const * s);

enum Types {IntType, FloatType, NULLType};
enum TerminalTypes {INIT, ProgramType, VarType, SetType, ReadType, PrintType, IfType, IfelseType, WhileType, ForType, ToType, StepType, DoType, PlusType, MinusType, MultType, DivType, ColonType, SemicolonType, LessType, GreatType,EqualType, LessequalType, GreatequalType};

typedef struct Node{
  char name[256];
  enum Types type;
  union val{
    int i;
    float f;
  } u_val;
  struct Node *next;
} node_t;

typedef struct Tree{
  enum TerminalTypes type;
  struct Tree* child[5];
  struct Node* symbol;
  int i;
  float f;
  struct Tree *nextInstruction;
} tree_t;

enum Types heap = NULLType;

void addInstructionToParent(tree_t*, enum TerminalTypes);
void addInstructionToTree(tree_t*, enum TerminalTypes);
void addToExpr(node_t*, char*);
void addTypeToVariable(node_t*, char*);
tree_t* createBinaryNode(tree_t*, enum TerminalTypes, tree_t*, tree_t*);
void declareVariable(node_t*, char*);
void floatToHeap();
const char* getType(enum Types);
void intToHeap();
void printList(node_t*);
void raiseDuplicateVar(char* name);
void raiseInvalidType(char* name);
void raiseInvalidCompatibleTypes();
void raiseNoExistingVar(char* name);
void resetHeap();
void setTable();
void setTree();
void verifyID(node_t*, char*);


node_t* symbol;
node_t* lastInserted;
tree_t* syntax;
tree_t* lastInstruction;
tree_t* lastChild;

%}

%union{
  char* stringValue;
  char* terminal;
  char* type;
  float f;
  int i;
}

%token <type> INT FLOAT 
%token <stringValue> ID 
%token  PROGRAM VAR NUMI NUMF SET READ PRINT IF IFELSE
WHILE FOR TO STEP DO SUMA RESTA DIVIDE MULTI PAREND PARENI 
LLAVED LLAVEI COLON SEMICOLON MENOR MAYOR IGUAL MENORI MAYORI



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

tipo : INT {addTypeToVariable(symbol, yylval.type);}
     | FLOAT {addTypeToVariable(symbol, yylval.type);}
;

stmt : assig_stmt
     | if_stmt
     | iter_stmt
     | cmp_stmt
;

assig_stmt : SET ID {verifyID(symbol, yylval.stringValue);} expr {resetHeap();} SEMICOLON {addInstructionToTree(syntax, ColonType);}
           | READ ID {verifyID(symbol, yylval.stringValue);} SEMICOLON {addInstructionToTree(syntax, ColonType);} 
           | PRINT expr {resetHeap();} SEMICOLON {addInstructionToTree(syntax, ColonType);}
;

if_stmt : IF PARENI expresion {resetHeap();} PAREND stmt 
        | IFELSE PARENI expresion {resetHeap();} PAREND stmt stmt 
;

iter_stmt : WHILE PARENI expresion {resetHeap();} PAREND stmt 
          | FOR SET ID {verifyID(symbol, yylval.stringValue);} expr {resetHeap();} TO expr {resetHeap();} STEP expr {resetHeap();} DO stmt 
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

factor : PARENI expr {resetHeap();} PAREND 
       | ID {addToExpr(symbol, yylval.stringValue);}
       | NUMI {intToHeap();}
       | NUMF {floatToHeap();}
;

expresion : expr MENOR expr {addInstructionToTree(syntax, LessType);}
          | expr MAYOR expr {addInstructionToTree(syntax, GreatType);}
          | expr IGUAL expr {addInstructionToTree(syntax, EqualType);}
          | expr MENORI expr {addInstructionToTree(syntax, LessequalType);}
          | expr MAYORI expr {addInstructionToTree(syntax, GreatequalType);}
;

%%
/*
 ! Puede que este método no sea necesario, ya no se necesita un registro de la posición

@param parent new instruction's parent 
@param instr  instruction to add to the parent

Inserts the action of the instruction, usually to a semicolon
*/
void addInstructionToParent(tree_t *parent, enum TerminalTypes type){
  /*
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = type;
  newNode->nextInstruction = NULL;
  newNode->pos = 0;
  parent->child[parent->pos] = newNode;
  parent->pos = parent->pos + 1;
  lastChild = newNode;
  */
}

/*
@param root   syntax tree's current root 
@param instr  instruction to add to the tree

Inserts a new instruction to the tree, usually
when it ends with a semicolon
*/
void addInstructionToTree(tree_t *root, enum TerminalTypes type){
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = type;
  newNode->nextInstruction = NULL;
  lastInstruction->nextInstruction = newNode;
}

/*
@param head   symbol's table head
@param name   variable trying to evaluate

Validates if current variables are the same type
*/
void addToExpr(node_t *head, char *name){
  node_t * current = head;
  while(current->next != NULL){
    current = current->next;
    if (strcmp(current->name, name) == 0){
      if(heap == NULLType){
        heap =  current->type;
      }else{
        if(heap != current->type){
          raiseInvalidCompatibleTypes();
        }
      }
    }
  }
}

/*
@param head   symbol's table head
@param type   type to add

Adds the type to the last inserted symbol
*/
void addTypeToVariable(node_t *head, char *type){
  if (strcmp(type, "int") == 0){
    lastInserted->type = IntType;
  }else{
    lastInserted->type = FloatType;
  }
}

/*
@param root   syntax tree
@param type   tree type
@param left   left side of expr
@param right  right side of expr

Returns pointer to tree node with the expresion build
*/
tree_t* createBinaryNode(tree_t *root, enum TerminalTypes type, tree_t *left, tree_t *right){
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = type;
  newNode->nextInstruction = NULL;
  newNode->child[0] = left;
  newNode->child[1] = right;
}

/*
@param head   symbol's table head
@param name   variable's name

Adds the variable to the symbol table, raises error 
if found previously
*/
void declareVariable(node_t *head, char *name){
  node_t *current = head;
  while(current->next != NULL){
    current = current->next;
    if (strcmp(current->name, name) == 0){
      raiseDuplicateVar(name);
    }
  }
  node_t * newNode = (node_t*)malloc(sizeof(node_t));
  current->next = newNode;
  strcpy(newNode->name, name);
  lastInserted = newNode;
}

/*
Validates if float was the last value in heap
*/
void floatToHeap(){
  if(heap == NULLType){
    heap =  FloatType;
  }else{
    if(heap != FloatType){
      raiseInvalidCompatibleTypes();
    }
  }
}

/*
@param type   type of the variable to print it

Returns variable as string (char*)
*/
const char* getType(enum Types type) {
  switch (type) {
    case IntType: return "int";
    case FloatType: return "float";
  }
}

/*
Validates if int was the last value in heap
*/
void intToHeap(){
  if(heap == NULLType){
    heap =  IntType;
  }else{
    if(heap != IntType){
      raiseInvalidCompatibleTypes();
    }
  }
}

/*
@param head   symbol's table head

Prints symbol's table when the program finishes
*/
void printList(node_t *head){
  if(head != NULL){
    printf("%s : %s\n", head->name, getType(head->type));
    printList(head->next);
  }
}

/*
@param name   duplicated var name

Raises error and exits program if a variable is tried
to be declared twice
*/
void raiseDuplicateVar(char *name){
  printf("La variable %s ya ha sido declarada\n",name);
  exit(0);
}

/*
@param name   incompatible type var

Raises error and exits program if a variable is tried
to get assigned to a wrong value
*/
void raiseInvalidType(char *name){
  printf("La variable %s tiene otro tipo de dato\n",name);
  exit(0);
}

/*
Raises error and exits program if two variables of 
different types are used in a expression
*/
void raiseInvalidCompatibleTypes(){
  printf("Las variables tienen distintos tipos de dato y no pueden ser utilizarse en la misma operación\n");
  exit(0);
}

/*
@param name   Unexistent variable name

Raises error and exits program if a variable is
trying to be accessed without been declared
*/
void raiseNoExistingVar(char *name){
  printf("La variable %s no ha sido declarada\n",name);
  exit(0);
}

/*
Resets the current type in the heap for future 
expression evaluation
*/
void resetHeap(){
  heap = NULLType;
}

/*
Initializes the table
*/
void setTable(){
  symbol = (node_t*)malloc(sizeof(node_t));
  strcpy(symbol->name, "__init__");
  symbol->next = NULL;
  lastInserted = symbol;
}

/*
Initializes the syntax tree
*/
void setTree(){
  syntax = (tree_t*)malloc(sizeof(tree_t));
  syntax->type = INIT;
  syntax->nextInstruction = NULL;
  lastInstruction = syntax;
}

/*
@param head   symbol's table head
@param name   variable to be found

Checks if variable exists, raises error if not found
*/
void verifyID(node_t *head, char *name){
  node_t * current = head;
  bool exists = false;
  while(current->next != NULL){
    current = current->next;
    if (strcmp(current->name, name) == 0){
      exists = true;
    }
  }
  if(exists == false){
    raiseNoExistingVar(name);
  }
}

int yyerror(char const * s) {
  fprintf(stderr, "%s\n", s);
}

int main(int argc, char **argv) {
  yyin = fopen(argv[1], "r+"); 
  setTable();
  setTree();
  yyparse();
  printf("Tabla de símbolos:\n");
  printList(symbol->next);
}
