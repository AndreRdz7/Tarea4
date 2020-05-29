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
enum TreeNodeTypes{INIT, MayorNode, MenorNode, IgualNode, MenorINode, MayorINode, InstruccionNode, IdNode, ExprNode, ReadNode, PrintNode, IfNode, ExpresionNode, IfelseNode, WhileNode, ForNode, SetNode, ComparandumNode, RestaNode, SumaNode, MultNode, DivideNode, TermNode, IntNode, FloatNode};

typedef struct expr{
  enum Types type;
  int i;
  float f;
} expr_t;

typedef struct Node{
  char name[256];
  enum Types type;
  union val{
    int i;
    float f;
  } u_val;
  struct Node * next;
} node_t;

typedef struct Tree{
  enum TreeNodeTypes type;
  int numberOfChilds;
  struct Tree * child[5]; 
  struct Node ** symbol; // in case that the type is an id (es doble pointer ya que si quiero editarlo la copia no me servira)
  int i;  // the i and f are for when there is an integer or float type (keeps the value)
  float f;
  struct Tree *nextInstruction; // every semcilomn there will be a new isntruction
} tree_t;

enum Types heap = NULLType;

// TREE functions:
// creates the tree
void setTree();
// add instruction node
void addInstructionToTree(enum TreeNodeTypes nodeType);
// create a node that has wo childs (expr, term, expresion)
void pushStackLastInstruccion();
void popStackLastInstruccion();
tree_t* createBinaryNode(enum TreeNodeTypes, tree_t*, tree_t*);
tree_t* addTreeIdNode(enum TreeNodeTypes, node_t**);
tree_t* addTreeIntNode(enum TreeNodeTypes, int);
tree_t* addTreeFloatNode(enum TreeNodeTypes, float);
char* getTypeOfTree(enum TreeNodeTypes);
void GenerateNodeAccordingToType(enum TreeNodeTypes);
tree_t* connectWithInstruccion(tree_t *);
tree_t* createOnaryNode(enum TreeNodeTypes type, tree_t *);
tree_t* createTrinaryNode(enum TreeNodeTypes type, tree_t *, tree_t *, tree_t *);
tree_t* createFournaryNode(enum TreeNodeTypes type, tree_t *, tree_t *, tree_t *, tree_t*);
// tree evaluation functions
bool checkCompatibleStructTypes(expr_t first, expr_t second);
void treeEvaluateRead(tree_t*);
expr_t evaluateExpr(tree_t*);
bool evaluateExpression(tree_t*);

void treeEvaluatePrint(tree_t*);
void treeEvaluateSet(tree_t*);




// LIST functions
// creates the list
void setTable();
//check if ID exists
node_t ** verifyID(node_t*, char*);
//check if value exists and if the type is the same (taht we are keeping in the heap)
void addToExpr(node_t*, char*);
// int or float type selection
void addTypeToVariable(node_t*, char*);
// add element to the list if irt already existsed call an error
void declareVariable(node_t*, char*);
// checdk if last element in the heap was a float
void floatToHeap();
// checdk if last element in the heap was a int
void intToHeap();
// print tyoe according to the enum (int and float)
const char* getType(enum Types);
// print the list
void printList(node_t*);
// reset the heap value
void resetHeap();

//ERRORS
void raiseDuplicateVar(char* name);
void raiseInvalidType(char* name);
void raiseInvalidCompatibleTypes();
void raiseNoExistingVar(char* name);



node_t* symbol; // start of the symbol linked list
node_t* lastInserted; // last element inserted in the linked list

tree_t* syntax; //start of the syntax tree


int heighStack = -1;
tree_t * stack_lastInstruccion[100]; // last instruction of the tree
node_t ** pointerToMemoryOfID;

%}

%union{
  char* stringValue;
  char* terminal;
  char* type;
  float f;
  int i;
  struct Tree *tree_t;
}

%type <tree_t> stmt expr term factor expresion if_stmt iter_stmt cmp_stmt assig_stmt stmt_lst;

%token <type> INT FLOAT;
%token <stringValue> ID;
%token  PROGRAM VAR NUMI NUMF SET READ PRINT IF IFELSE
WHILE FOR TO STEP DO SUMA RESTA DIVIDE MULTI PAREND PARENI 
LLAVED LLAVEI COLON SEMICOLON MENOR MAYOR IGUAL MENORI MAYORI;



%start prog;

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

stmt : {addInstructionToTree(InstruccionNode);} assig_stmt {$$ = $2;}
     | if_stmt {$$ = $1;}
     | iter_stmt {$$ = $1;}
     | cmp_stmt {$$ = $1;}
;


assig_stmt : SET ID {pointerToMemoryOfID = verifyID(symbol, yylval.stringValue);} expr {resetHeap();} SEMICOLON {$$ = connectWithInstruccion(createBinaryNode(SetNode, addTreeIdNode(IdNode, pointerToMemoryOfID), $4));}
           | READ ID {pointerToMemoryOfID = verifyID(symbol, yylval.stringValue);} SEMICOLON {$$ = connectWithInstruccion(createOnaryNode(ReadNode, addTreeIdNode(IdNode, pointerToMemoryOfID)));}
           | PRINT expr {resetHeap();} SEMICOLON {$$ = connectWithInstruccion(createOnaryNode(PrintNode, $2));}
;

if_stmt : IF PARENI expresion {resetHeap();} PAREND stmt {$$ = connectWithInstruccion(createBinaryNode(IfNode,$3, $6));}
        | IFELSE PARENI expresion {resetHeap();} PAREND stmt stmt {$$ = connectWithInstruccion(createTrinaryNode(IfelseNode, $3, $6, $7));}
;

iter_stmt : WHILE PARENI expresion {resetHeap();} PAREND stmt {$$ = connectWithInstruccion(createBinaryNode(WhileNode, $3, $6));}
          | FOR SET ID {pointerToMemoryOfID = verifyID(symbol, yylval.stringValue);} expr {resetHeap();} TO expr {resetHeap();} STEP expr {resetHeap();} DO stmt {$$ = connectWithInstruccion(createFournaryNode(ForNode, createBinaryNode(SetNode, addTreeIdNode(IdNode, pointerToMemoryOfID), $5), $8, $11, $14));}
;

cmp_stmt : LLAVEI LLAVED {$$ = NULL;}
         | LLAVEI {pushStackLastInstruccion();} stmt_lst {popStackLastInstruccion();} LLAVED {$$ = $3;}
;

stmt_lst : stmt {$$ = $1;}
         | stmt_lst stmt {$$ = $2;}
;

expr : expr SUMA term {$$ = createBinaryNode(SumaNode, $1, $3);}
     | expr RESTA term {$$ = createBinaryNode(RestaNode, $1, $3);}
     | term {$$ = $1;}
;

term : term MULTI factor {$$ = createBinaryNode(MultNode, $1, $3);}
     | term DIVIDE factor {$$ = createBinaryNode(DivideNode, $1, $3);}
     | factor {$$ = $1;}

factor : PARENI expr PAREND {$$ = $2;}
       | ID {addToExpr(symbol, yylval.stringValue); $$ = addTreeIdNode(IdNode, verifyID(symbol, yylval.stringValue));}
       | NUMI {intToHeap(); $$ = addTreeIntNode(IntNode, yylval.i);}
       | NUMF {floatToHeap(); $$ = addTreeFloatNode(FloatNode, yylval.f);} 
;

expresion : expr MENOR expr {$$ = createBinaryNode(MenorNode, $1, $3);}
          | expr MAYOR expr {$$ = createBinaryNode(MayorNode, $1, $3);}
          | expr IGUAL expr {$$ = createBinaryNode(IgualNode, $1, $3);}
          | expr MENORI expr {$$ = createBinaryNode(MenorINode, $1, $3);}
          | expr MAYORI expr {$$ = createBinaryNode(MayorINode, $1, $3);}
;

%%

char* getTypeOfTree(enum TreeNodeTypes type) 
{
      switch (type) 
      {
            case InstruccionNode: return "instruccion";
            case INIT: return "init";
            case IdNode: return "id";
            case ExprNode: return "expr";
            case ReadNode: return "read";
            case PrintNode: return "print";
            case IfNode: return "if";
            case ExpresionNode: return "expression";
            case IfelseNode: return "ifelse";
            case WhileNode: return "while";
            case ForNode: return "for";
            case SetNode: return "set";
            case ComparandumNode: return "comparandum";
            case TermNode: return "term";
            case SumaNode: return "suma";
            case RestaNode: return "resta";
            case DivideNode: return "divisi";
            case MultNode: return "mult";
            case IntNode: return "int";
            case FloatNode: return "float";
            case MenorNode: return "menor";
            case MenorINode: return "menor igual";
            case MayorINode: return "mayor igual";
            case MayorNode: return "mayor";
            case IgualNode: return "igual";
            default: return "there was an error";
      }
}

void GenerateNodeAccordingToType(enum TreeNodeTypes type) 
{
      switch (type) 
      {     // ultimo nodo, aqui se guarda int
            case IntType:

            break;
            // ultimo nodo, aqui guardo float
            case FloatType:

            break;
            // ultimo nodo, aqui se guarda el puntero al id
            case IdNode:

            break;
            // de aqui puede haber expr-term o term, el valor, en teoria guardamos el signo
            case ExprNode:

            break;
            // read node, de aqui abajo solo hay un id
            case ReadNode:

            break;
            // de aqui hay una exr
            case PrintNode:

            break;
            // de aqui hay una expr y otra cosa
            case IfNode:

            break;
            case ExpresionNode:

            break;
            case IfelseNode:

            break;
            case WhileNode:

            break;
            case ForNode:

            break;
            case SetNode:

            break;
            case ComparandumNode:

            break;
            case TermNode:

            break;
      }
}

tree_t* connectWithInstruccion(tree_t * subtree){
  printf("Connecto, subgrafo a la instruccion actual, el tipo del subgrafo es: %s\n",getTypeOfTree(subtree->type));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  (stack_lastInstruccion[heighStack])->numberOfChilds++;
  (stack_lastInstruccion[heighStack])->child[(stack_lastInstruccion[heighStack])->numberOfChilds] = subtree;
  return newNode;
}


void treeEvaluateRead(tree_t *node){
  // user input
  char input[256];
  char decimal[] = ".";
  scanf("%s", input);
  bool isInt;
  // get type by finding a decimall point
  char *ptr = strstr(input, decimal);
  // si es NULL, no encontro punto decimal, por lo tanto es entero
  int i_val;
  float f_val;
  if(ptr != NULL){ //float
    f_val = atof(input);
    isInt = false;
  }else{ // int
    i_val = atoi(input);
    isInt = true;
  }
  // insert value in symbol
  node_t* sym = *node->symbol;
  if(sym->type == IntType && isInt){
    sym->u_val.i = i_val;
  }else if(sym->type == FloatType && !isInt){
    sym->u_val.f = f_val;
  }else{
    raiseInvalidCompatibleTypes();
  }
}

bool checkCompatibleStructTypes(expr_t first, expr_t second){
  if(first.type == second.type){
    return true;
  }else{
    raiseInvalidCompatibleTypes();
  }
}

bool evaluateExpression(tree_t *node){
  expr_t left = evaluateExpr(node->child[0]);
  expr_t right = evaluateExpr(node->child[1]);
  switch(node->type){
    case MenorNode:;
      if(checkCompatibleStructTypes(left, right)){
        if(left.type == IntType){
          if(left.i < right.i){
            return true;
          }else{
            return false;
          }
        }else{
          if(left.f < right.f){
            return true;
          }else{
            return false;
          }
        }
      }
      break;
    case MayorNode:;
      if(checkCompatibleStructTypes(left, right)){
        if(left.type == IntType){
          if(left.i > right.i){
            return true;
          }else{
            return false;
          }
        }else{
          if(left.f > right.f){
            return true;
          }else{
            return false;
          }
        }
      }
      break;
    case IgualNode:;
      if(checkCompatibleStructTypes(left, right)){
        if(left.type == IntType){
          if(left.i == right.i){
            return true;
          }else{
            return false;
          }
        }else{
          if(left.f == right.f){
            return true;
          }else{
            return false;
          }
        }
      }
      break;
    case MenorINode:;
      if(checkCompatibleStructTypes(left, right)){
        if(left.type == IntType){
          if(left.i <= right.i){
            return true;
          }else{
            return false;
          }
        }else{
          if(left.f <= right.f){
            return true;
          }else{
            return false;
          }
        }
      }
      break;
    case MayorINode:;
      if(checkCompatibleStructTypes(left, right)){
        if(left.type == IntType){
          if(left.i >= right.i){
            return true;
          }else{
            return false;
          }
        }else{
          if(left.f >= right.f){
            return true;
          }else{
            return false;
          }
        }
      }
      break;
  }
}

expr_t evaluateExpr(tree_t *node){
  expr_t left;
  expr_t right;
  expr_t res;
  switch(node->type){
    case SumaNode:;
      left = evaluateExpr(node->child[0]);
      right = evaluateExpr(node->child[1]);
      if(checkCompatibleStructTypes){
        if(left.type == IntType){
          res.type = IntType;
          res.i = left.i + right.i;
          return res;
        }else{
          res.type = FloatType;
          res.f = left.f + right.f;
          return res;
        }
      }
      break;
    case RestaNode:;
      left = evaluateExpr(node->child[0]);
      right = evaluateExpr(node->child[1]);
      if(checkCompatibleStructTypes){
        res;
        if(left.type == IntType){
          res.type = IntType;
          res.i = left.i - right.i;
          return res;
        }else{
          res.type = FloatType;
          res.f = left.f - right.f;
          return res;
        }
      }
      break;
    case MultNode:;
      left = evaluateExpr(node->child[0]);
      right = evaluateExpr(node->child[1]);
      if(checkCompatibleStructTypes){
        res;
        if(left.type == IntType){
          res.type = IntType;
          res.i = left.i * right.i;
          return res;
        }else{
          res.type = FloatType;
          res.f = left.f * right.f;
          return res;
        }
      }
      break;
    case DivideNode:;
      left = evaluateExpr(node->child[0]);
      right = evaluateExpr(node->child[1]);
      if(checkCompatibleStructTypes){
        res;
        if(left.type == IntType){
          res.type = IntType;
          res.i = left.i / right.i;
          return res;
        }else{
          res.type = FloatType;
          res.f = left.f / right.f;
          return res;
        }
      }
      break;
    case IntNode:;
      res.type = IntType;
      res.i = node->i;
      return res;
      break;
    case FloatNode:;
    res.type = FloatType;
      res.i = node->f;
      return res;
      break;
    case IdNode:;
      node_t* sym = *node->symbol;
      if(sym->type == IntType){
        res.i = sym->u_val.i;
        return res;
      }else{
        res.f = sym->u_val.f;
        return res;
      }
      break;
  }
}

tree_t* createFournaryNode(enum TreeNodeTypes type, tree_t * one, tree_t * two, tree_t * three, tree_t* four){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(type));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = type;
  newNode->nextInstruction = NULL;
  newNode->numberOfChilds = -1;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = one;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = two;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = three;
    newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = four;
  return newNode;
}

tree_t* createTrinaryNode(enum TreeNodeTypes type, tree_t * one, tree_t * two, tree_t * three){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(type));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = type;
  newNode->nextInstruction = NULL;
  newNode->numberOfChilds = -1;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = one;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = two;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = three;
  return newNode;
}

tree_t* createBinaryNode(enum TreeNodeTypes type, tree_t *left, tree_t *right){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(type));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = type;
  newNode->nextInstruction = NULL;
  newNode->numberOfChilds = -1;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = left;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = right;
  return newNode;
}

tree_t* createOnaryNode(enum TreeNodeTypes type, tree_t *child){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(type));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = type;
  newNode->nextInstruction = NULL;
  newNode->numberOfChilds = -1;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = child;
  return newNode;
}

void pushStackLastInstruccion(){
  printf("Creo nueva lista de instrucciones\n");

  if(stack_lastInstruccion[heighStack]->type != INIT){
    heighStack++;
  }
}

void popStackLastInstruccion(){
  printf("Termino lista de instrucciones y regreso a la pasada\n");
  stack_lastInstruccion[heighStack] = NULL;
  heighStack--;
}


tree_t* addTreeIdNode(enum TreeNodeTypes actualNodeToAddType, node_t ** pointerId){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));

  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->symbol = pointerId;
  stack_lastInstruccion[heighStack]->numberOfChilds++;
  stack_lastInstruccion[heighStack]->child[stack_lastInstruccion[heighStack]->numberOfChilds] = newNode;
  return newNode;
}

tree_t* addTreeIntNode(enum TreeNodeTypes actualNodeToAddType, int value){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));

  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->i = value;
  stack_lastInstruccion[heighStack]->numberOfChilds++;
  stack_lastInstruccion[heighStack]->child[stack_lastInstruccion[heighStack]->numberOfChilds] = newNode;
  return newNode;
}

tree_t* addTreeFloatNode(enum TreeNodeTypes actualNodeToAddType, float value){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));

  tree_t* newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->f = value;
  stack_lastInstruccion[heighStack]->numberOfChilds++;
  stack_lastInstruccion[heighStack]->child[stack_lastInstruccion[heighStack]->numberOfChilds] = newNode;
  return newNode;
}

/*
@param root   syntax tree's current root 
@param instr  instruction to add to the tree

Inserts a new instruction to the tree, usually
when it ends with a semicolon
*/
// solo agrego instrucciones en el mismo nivel
void addInstructionToTree(enum TreeNodeTypes nodeType){
  printf("Agrego Instruccion\n");
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = nodeType;
  newNode->nextInstruction = NULL;

  if(stack_lastInstruccion[heighStack] != NULL){
    stack_lastInstruccion[heighStack]->nextInstruction = newNode;
  }

  //connect with last instruction
  stack_lastInstruccion[heighStack] = newNode;

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
    lastInserted->u_val.i = 0;
  }else{
    lastInserted->type = FloatType;
    lastInserted->u_val.f = 0.0;
  }
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
    if(head->type == IntType){
      printf("%s - %s : %d\n", head->name, getType(head->type), (head->u_val).i);

    }else{
      printf("%s - %s : %f\n", head->name, getType(head->type), (head->u_val).f);
    } 
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
  syntax->numberOfChilds = -1;
  heighStack++;
  stack_lastInstruccion[heighStack] = syntax;
}

/*
@param head   symbol's table head
@param name   variable to be found

Checks if variable exists, raises error if not found
*/
node_t ** verifyID(node_t *head, char *name){
  printf("Verifico %s\n", name);
  node_t ** current = &head;

  while((*current)->next != NULL){
    current = &((*current)->next);
    if (strcmp((*current)->name, name) == 0){
      return current;
    }
  }

  raiseNoExistingVar(name);
  
}

int yyerror(char const * s) {
  fprintf(stderr, "%s\n", s);
}

void execute(tree_t* actualInstruction){
  printf("type:%s\n", getTypeOfTree(actualInstruction->type));
  
  if(actualInstruction->nextInstruction != NULL){
    execute( (actualInstruction->nextInstruction) );
  }
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

  setTable();
  setTree();
  yyparse();
  printf("Tabla de símbolos:\n");
  printList(symbol->next);
  printf("Ejecutar codigo:\n");
  execute(syntax);
}