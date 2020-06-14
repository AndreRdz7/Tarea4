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
enum TreeNodeTypes{INIT, FuncionNode , MayorNode, MenorNode, IgualNode, MenorINode, MayorINode, InstruccionNode, IdNode, ExprNode, ReturnNode, ReadNode, PrintNode, IfNode, ExpresionNode, IfelseNode, WhileNode, ForNode, SetNode, ComparandumNode, RestaNode, SumaNode, MultNode, DivideNode, TermNode, IntNode, FloatNode};

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
  struct Func * funcNode;
} tree_t;

typedef struct Func{
  char name[256];
  enum Types returnType;
  int i;
  float f;
  struct Func * next;
  int numParams;
  bool firstInstruction;
  struct Tree * syntaxRoot;
  struct Node * symbolRoot;
  node_t* lastInserted;
  int heighInstructionStack;
  tree_t * stack_lastInstruccion[100];
} func_t;

int heighFuncStack = -1;
func_t * stackFunctions[1000];



enum Types heap = NULLType;

// TREE functions:
// creates the tree
void setTree();
// add instruction node
void addInstructionToTree(enum TreeNodeTypes nodeType, func_t*);
// create a node that has wo childs (expr, term, expresion)
void pushStackLastInstruccion(func_t * );
void popStackLastInstruccion(func_t *);
tree_t* createBinaryNode(enum TreeNodeTypes, tree_t*, tree_t*);
tree_t* addTreeIdNode(enum TreeNodeTypes, node_t**);
tree_t* addTreeIntNode(enum TreeNodeTypes, int);
tree_t* addTreeFloatNode(enum TreeNodeTypes, float);
char* getTypeOfTree(enum TreeNodeTypes);
void GenerateNodeAccordingToType(enum TreeNodeTypes);
tree_t* connectWithInstruccion(tree_t *, func_t *);
tree_t* createUnaryNode(enum TreeNodeTypes type, tree_t *);
tree_t* createTernaryNode(enum TreeNodeTypes type, tree_t *, tree_t *, tree_t *);
tree_t* createQuaternaryNode(enum TreeNodeTypes type, tree_t *, tree_t *, tree_t *, tree_t*);
// tree evaluation functions
bool checkCompatibleStructTypes(expr_t first, expr_t second);
void treeEvaluateRead(tree_t*);
expr_t evaluateExpr(tree_t*);
bool evaluateExpression(tree_t*);
void treeEvaluatePrint(tree_t*);
void treeEvaluateSet(tree_t*);
void treeEvaluateIf(tree_t*);
void treeEvaluateIfElse(tree_t*);
void treeEvaluateWhile(tree_t*);
void treeEvaluateFor(tree_t*);
tree_t * returnLastInstrucc(tree_t*);

void assignTreeToFunction();
// LIST functions
// creates the list
node_t * setTable();
//check if ID exists
node_t ** verifyID(node_t*, char*);
//check if value exists and if the type is the same (taht we are keeping in the heap)
void addToExpr(node_t*, char*);
// int or float type selection
void removeFromExpr(node_t *, char *);
void addTypeToVariable(char*, func_t*);


void addTypeToFunction(char*);
// add element to the list if irt already existsed call an error
void declareVariable(node_t*, char*, func_t*);
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

// EXEC Functions Functions ._.XD
bool evaluatePameters(tree_t* node){}





// functions of creating functions
void declareFunction(func_t*, char*);
func_t ** verifyFunctionID(func_t*, char*);
void printFunctionList(func_t*);


void pushFunctionInStack(func_t * fun);

void popFunctionInStack();

void setGlobals(char *);
func_t * createFunc(char *, enum Types);

//ERRORS
void raiseDuplicateVar(char* name);
void raiseInvalidType(char* name);
void raiseInvalidCompatibleTypes();
void raiseNoExistingVar(char* name);
void raiseInvalidParameterType(char* name);
void raiseInvalidAmountOfParameters();


// symbol, last Inserted , syntax, stack function height and the stack of main function
// by every func created a new symbol, lastInserted, syntax, heigh and stack will be declared
// and stored in the node of function
func_t * globalFunc;


func_t * fsymbol; // start of the linked list of functions
func_t * lastFuncionInserted; // last function declared

char * idName;
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

%type <tree_t> factor_id opt_exprs expr_lst fun_op fun_dec stmt expr term factor expresion if_stmt iter_stmt cmp_stmt assig_stmt stmt_lst;

%token <type> INT FLOAT;
%token <stringValue> ID;
%token FUN PROGRAM VAR NUMI NUMF SET READ PRINT IF IFELSE
WHILE FOR TO STEP DO SUMA RESTA DIVIDE MULTI PAREND PARENI 
LLAVED LLAVEI COLON SEMICOLON MENOR MAYOR IGUAL MENORI MAYORI COMMA RETURN ;

%start prog;

%%

prog : PROGRAM ID {setGlobals(yylval.stringValue);} LLAVEI opt_decls opt_fun_decls LLAVED stmt 
;

opt_decls : decls 
          | %empty 
;

decls : dec SEMICOLON decls 
      | dec
;

dec : VAR ID {declareVariable(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue, stackFunctions[heighFuncStack]);} COLON tipo {addTypeToVariable(yylval.type, stackFunctions[heighFuncStack]);}
;

tipo : INT
     | FLOAT
;

opt_fun_decls : fun_decls 
              | %empty
;

fun_decls : fun_decls fun_dec
          | fun_dec
;

fun_dec : FUN ID {declareFunction(fsymbol, yylval.stringValue);} PARENI oparams PAREND COLON tipo {addTypeToFunction(yylval.type);} fun_op {popFunctionInStack();}
;

fun_op : LLAVEI opt_decls LLAVED stmt {$$ = $4;}
       | SEMICOLON
;

oparams : params 
        | %empty
;

params : param COMMA params 
       | param
;

param : VAR ID {declareVariable(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue, stackFunctions[heighFuncStack]);} COLON tipo {addTypeToVariable(yylval.type, stackFunctions[heighFuncStack]);}
;

stmt : {addInstructionToTree(InstruccionNode, stackFunctions[heighFuncStack]);} assig_stmt {$$ = $2;}
     | if_stmt {$$ = $1;}
     | iter_stmt {$$ = $1;}
     | cmp_stmt {$$ = $1;}
;


assig_stmt : SET ID {pointerToMemoryOfID = verifyID(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue);} expr {resetHeap();} SEMICOLON {$$ = connectWithInstruccion(createBinaryNode(SetNode, addTreeIdNode(IdNode, pointerToMemoryOfID), $4), stackFunctions[heighFuncStack]);}
           | READ ID {pointerToMemoryOfID = verifyID(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue);} SEMICOLON {$$ = connectWithInstruccion(createUnaryNode(ReadNode, addTreeIdNode(IdNode, pointerToMemoryOfID)), stackFunctions[heighFuncStack]);}
           | PRINT expr {resetHeap();} SEMICOLON {$$ = connectWithInstruccion(createUnaryNode(PrintNode, $2), stackFunctions[heighFuncStack]);}
           | RETURN expr {resetHeap(); printf("Termino de leer expr de return\n");} SEMICOLON {$$ = connectWithInstruccion(createUnaryNode(ReturnNode, $2), stackFunctions[heighFuncStack]);}
;

if_stmt : IF PARENI expresion {resetHeap();} PAREND stmt {$$ = connectWithInstruccion(createBinaryNode(IfNode,$3, $6), stackFunctions[heighFuncStack]);}
        | IFELSE PARENI expresion {resetHeap();} PAREND stmt stmt {$$ = connectWithInstruccion(createTernaryNode(IfelseNode, $3, $6, $7), stackFunctions[heighFuncStack]);}
;

iter_stmt : WHILE PARENI expresion {resetHeap();} PAREND stmt {$$ = connectWithInstruccion(createBinaryNode(WhileNode, $3, $6), stackFunctions[heighFuncStack]);}
          | FOR SET ID {pointerToMemoryOfID = verifyID(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue);} expr {resetHeap();} TO expr {resetHeap();} STEP expr {resetHeap();} DO stmt {$$ = connectWithInstruccion(createQuaternaryNode(ForNode, createBinaryNode(SetNode, addTreeIdNode(IdNode, pointerToMemoryOfID), $5), $8, $11, $14), stackFunctions[heighFuncStack]);}
;

cmp_stmt : LLAVEI LLAVED {$$ = NULL;}
         | LLAVEI {pushStackLastInstruccion(stackFunctions[heighFuncStack]);} stmt_lst {popStackLastInstruccion(stackFunctions[heighFuncStack]);} LLAVED {$$ = $3;}
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
       | ID {idName = $1; addToExpr(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue);} factor_id
       | NUMI {intToHeap(); $$ = addTreeIntNode(IntNode, yylval.i);}
       | NUMF {floatToHeap(); $$ = addTreeFloatNode(FloatNode, yylval.f);}
;

factor_id : PARENI {removeFromExpr(stackFunctions[heighFuncStack]->symbolRoot, idName);} opt_exprs PAREND
          | %empty 
; 


opt_exprs : expr_lst
          | %empty
;

expr_lst : expr_lst COMMA expr {connectWithInstruccion($3, stackFunctions[heighFuncStack]);}
         | expr {connectWithInstruccion($1, stackFunctions[heighFuncStack]);}
;

expresion : expr MENOR expr {$$ = createBinaryNode(MenorNode, $1, $3);}
          | expr MAYOR expr {$$ = createBinaryNode(MayorNode, $1, $3);}
          | expr IGUAL expr {$$ = createBinaryNode(IgualNode, $1, $3);}
          | expr MENORI expr {$$ = createBinaryNode(MenorINode, $1, $3);}
          | expr MAYORI expr {$$ = createBinaryNode(MayorINode, $1, $3);}
;

%%

char* getTypeOfTree(enum TreeNodeTypes type) {
  switch (type) {
    case FuncionNode: return "funcion";
    case InstruccionNode: return "instruccion";
    case INIT: return "init";
    case IdNode: return "id";
    case ExprNode: return "expr";
    case ReadNode: return "read";
    case ReturnNode: return "return";
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

// refactored
tree_t* connectWithInstruccion(tree_t * subtree, func_t * actualScope){
  printf("Connecto, subgrafo a la instruccion actual, el tipo del subgrafo es: %s\n",getTypeOfTree(subtree->type));
  printf("Actual heigh of stack: %d\n", actualScope->heighInstructionStack);

  if(actualScope->heighInstructionStack > -1){
    tree_t * lastNodeInList = returnLastInstrucc(actualScope->stack_lastInstruccion[actualScope->heighInstructionStack]);
    printf("Es: %s\n",getTypeOfTree(lastNodeInList->type));
    lastNodeInList->numberOfChilds = lastNodeInList->numberOfChilds + 1;
    lastNodeInList->child[lastNodeInList->numberOfChilds] = subtree;
    return (actualScope->stack_lastInstruccion[actualScope->heighInstructionStack]);
  }else{
    actualScope->syntaxRoot = subtree;
    return actualScope->syntaxRoot;
  }

}


void treeEvaluateRead(tree_t *node){
  char input[256];
  char decimal[] = ".";
  scanf("%s", input);
  bool isInt;
  char *ptr = strstr(input, decimal);
  int i_val;
  float f_val;
  if(ptr != NULL){ //float
    f_val = atof(input);
    isInt = false;
  }else{ // int
    i_val = atoi(input);
    isInt = true;
  }
  node_t* sym = *node->child[0]->symbol;
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

void treeEvaluatePrint(tree_t *node){
  //printf("printing... ");
  expr_t stmt = evaluateExpr(node->child[0]);
  if(stmt.type == IntType){
    printf("%d\n", stmt.i);
  }else{
    printf("%f\n", stmt.f);
  }
}

void treeEvaluateSet(tree_t *node){
  /*
  child 0 es el tree_t con el id de la tabla de simbolos
  chils 1 es la expresión a asignar
  */
  expr_t id = evaluateExpr(node->child[0]);
  expr_t stmt = evaluateExpr(node->child[1]);
  node_t* sym = *node->child[0]->symbol;
  if(checkCompatibleStructTypes(id, stmt)){
    if(strcmp(getType(id.type), "int") == 0){
      sym->u_val.i = stmt.i;
    }else{
      sym->u_val.f = stmt.f;
    }
  }
}

void treeEvaluateIf(tree_t *node){
  /*
  child 0 expression
  child 1 stmt
  */
  tree_t *stmt = node->child[1]->nextInstruction;
  if(evaluateExpression(node->child[0])){
    // execute stmt list
    while(stmt != NULL){
      switch(stmt->child[0]->type){
        case SetNode:
          treeEvaluateSet(stmt->child[0]);
          break;
        case ReadNode:
          treeEvaluateRead(stmt->child[0]);
          break;
        case PrintNode:
          treeEvaluatePrint(stmt->child[0]);
          break;
        case IfNode:
          treeEvaluateIf(stmt->child[0]);
          break;
        case IfelseNode:
          treeEvaluateIfElse(stmt->child[0]);
          break;
        case WhileNode:
          treeEvaluateWhile(stmt->child[0]);
          break;
        case ForNode:
          treeEvaluateFor(stmt->child[0]);
          break;
        default:
          break;
      }
      stmt = stmt->nextInstruction;
    }
  }else{
    return;
  }
}

/* void assignTreeToFunction(){
  func_t actualFunc = stackFunctions[heighFuncStack];
  pushFunctionInStack(actualFunc);
} */

void treeEvaluateIfElse(tree_t *node){
  /*
  child 0 expression
  child 1 stmt if true
  child 2 stmt if false
  */
  tree_t * stmtTrue = node->child[1]->nextInstruction;
  tree_t * stmtFalse = node->child[2]->nextInstruction;
  if(evaluateExpression(node->child[0])){
    while(stmtTrue != NULL){
      switch(stmtTrue->child[0]->type){
        case SetNode:
          treeEvaluateSet(stmtTrue->child[0]);
          break;
        case ReadNode:
          treeEvaluateRead(stmtTrue->child[0]);
          break;
        case PrintNode:
          treeEvaluatePrint(stmtTrue->child[0]);
          break;
        case IfNode:
          treeEvaluateIf(stmtTrue->child[0]);
          break;
        case IfelseNode:
          treeEvaluateIfElse(stmtTrue->child[0]);
          break;
        case WhileNode:
          treeEvaluateWhile(stmtTrue->child[0]);
          break;
        case ForNode:
          treeEvaluateFor(stmtTrue->child[0]);
          break;
      }
      stmtTrue = stmtTrue->nextInstruction;
    }
  }else{
    while(stmtFalse != NULL){
      switch(stmtFalse->child[0]->type){
        case SetNode:
          treeEvaluateSet(stmtFalse->child[0]);
          break;
        case ReadNode:
          treeEvaluateRead(stmtFalse->child[0]);
          break;
        case PrintNode:
          treeEvaluatePrint(stmtFalse->child[0]);
          break;
        case IfNode:
          treeEvaluateIf(stmtFalse->child[0]);
          break;
        case IfelseNode:
          treeEvaluateIfElse(stmtFalse->child[0]);
          break;
        case WhileNode:
          treeEvaluateWhile(stmtFalse->child[0]);
          break;
        case ForNode:
          treeEvaluateFor(stmtFalse->child[0]);
          break;
      }
      stmtFalse = stmtFalse->nextInstruction;
    }
  }
}

void treeEvaluateWhile(tree_t *node){
  /*
  child 0 condition
  child 1 stmt
  */
  tree_t *stmt = node->child[1]->nextInstruction;
  tree_t *whileFirstInstr = stmt;
  bool condition = evaluateExpression(node->child[0]);
  while(condition){
    while(stmt != NULL){
      switch(stmt->child[0]->type){
        case SetNode:
          treeEvaluateSet(stmt->child[0]);
          break;
        case ReadNode:
          treeEvaluateRead(stmt->child[0]);
          break;
        case PrintNode:
          treeEvaluatePrint(stmt->child[0]);
          break;
        case IfNode:
          treeEvaluateIf(stmt->child[0]);
          break;
        case IfelseNode:
          treeEvaluateIfElse(stmt->child[0]);
          break;
        case WhileNode:
          treeEvaluateWhile(stmt->child[0]);
          break;
        case ForNode:
          treeEvaluateFor(stmt->child[0]);
          break;
      }
      stmt = stmt->nextInstruction;
    }
    stmt = whileFirstInstr;
    condition = evaluateExpression(node->child[0]);
  }
}

void treeEvaluateFor(tree_t *node){
  /*
  child 0 init
  child 1 to
  child 2 step
  child 3 expr
  */
  expr_t init = evaluateExpr(node->child[0]);
  expr_t to = evaluateExpr(node->child[1]);
  expr_t step = evaluateExpr(node->child[2]);
  tree_t *stmt = node->child[3]->nextInstruction;
  tree_t *whileFirstInstr = stmt;
  if(checkCompatibleStructTypes(init, to)){
    if(checkCompatibleStructTypes(to, step)){
      // si todos son del mismo tipo, se ejecuta el for
      if(init.type == IntType){
        // todos son enteros
        for(init.i; to.i;){
          while(stmt != NULL){
            switch(stmt->child[0]->type){
              case SetNode:
                treeEvaluateSet(stmt->child[0]);
                break;
              case ReadNode:
                treeEvaluateRead(stmt->child[0]);
                break;
              case PrintNode:
                treeEvaluatePrint(stmt->child[0]);
                break;
              case IfNode:
                treeEvaluateIf(stmt->child[0]);
                break;
              case IfelseNode:
                treeEvaluateIfElse(stmt->child[0]);
                break;
              case WhileNode:
                treeEvaluateWhile(stmt->child[0]);
                break;
              case ForNode:
                treeEvaluateFor(stmt->child[0]);
                break;
            }
            stmt = stmt->nextInstruction;
          }
          stmt = whileFirstInstr;
          init.i += step.i;
        }
      }else{
        for(init.f; to.f;){
          while(stmt != NULL){
            switch(stmt->child[0]->type){
              case SetNode:
                treeEvaluateSet(stmt->child[0]);
                break;
              case ReadNode:
                treeEvaluateRead(stmt->child[0]);
                break;
              case PrintNode:
                treeEvaluatePrint(stmt->child[0]);
                break;
              case IfNode:
                treeEvaluateIf(stmt->child[0]);
                break;
              case IfelseNode:
                treeEvaluateIfElse(stmt->child[0]);
                break;
              case WhileNode:
                treeEvaluateWhile(stmt->child[0]);
                break;
              case ForNode:
                treeEvaluateFor(stmt->child[0]);
                break;
            }
            stmt = stmt->nextInstruction;
          }
          stmt = whileFirstInstr;
          init.f += step.f;
        }
      }
    }else{
      raiseInvalidCompatibleTypes();
    }
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
        res.type = IntType;
        return res;
      }else{
        res.f = sym->u_val.f;
        res.type = FloatType;
        return res;
      }
      break;
  }
}

bool evaluatePameters(tree_t *node){
  /*int no_params = node->funcNode->no_params*/
  int no_params = 1;
  if(no_params != node->numberOfChilds){
    raiseInvalidAmountOfParameters();
  }
}

tree_t* createQuaternaryNode(enum TreeNodeTypes type, tree_t * one, tree_t * two, tree_t * three, tree_t* four){
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
  newNode->child[4] = NULL;
  return newNode;
}

tree_t* createTernaryNode(enum TreeNodeTypes type, tree_t * one, tree_t * two, tree_t * three){
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
  newNode->child[3] = NULL;
  newNode->child[4] = NULL;
  return newNode;
}

tree_t* createBinaryNode(enum TreeNodeTypes type, tree_t *left, tree_t *right){
  printf("Creando Binary\n");
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(type));
  printf("Left: %s\n", getTypeOfTree(left->type));
  printf("hijos de left: %d\n", left->numberOfChilds+1);
  printf("Right: %s\n", getTypeOfTree(right->type));
  printf("hijos de right: %d\n", right->numberOfChilds+1);

  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = type;
  newNode->nextInstruction = NULL;
  newNode->numberOfChilds = -1;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = left;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = right;
  newNode->child[2] = NULL;
  newNode->child[3] = NULL;
  newNode->child[4] = NULL;
  return newNode;
}

tree_t* createUnaryNode(enum TreeNodeTypes type, tree_t *child){
  printf("Creando Unary\n");
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(type));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = type;
  newNode->nextInstruction = NULL;
  newNode->numberOfChilds = -1;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = child;
  newNode->child[1] = NULL;
  newNode->child[2] = NULL;
  newNode->child[3] = NULL;
  newNode->child[4] = NULL;
  return newNode;
}

//refactored
void pushStackLastInstruccion(func_t * scope){
  printf("Creo nueva lista de instrucciones\n");

  scope->heighInstructionStack++;
  tree_t * init_node = (tree_t*)malloc(sizeof(tree_t));
  init_node->type = INIT;
  init_node->nextInstruction = NULL;
  init_node->numberOfChilds = -1;
  scope->stack_lastInstruccion[scope->heighInstructionStack] = init_node;

  
  if(scope->firstInstruction){
    scope->syntaxRoot = init_node;
    scope->firstInstruction = false;
  }
}

// rfeactored
void popStackLastInstruccion(func_t * scope){
  printf("Termino lista de instrucciones y regreso a la pasada\n");
  scope->stack_lastInstruccion[scope->heighInstructionStack] = NULL;
  scope->heighInstructionStack--;
}

tree_t * returnLastInstrucc(tree_t * root){
  if(root->nextInstruction){
    returnLastInstrucc(root->nextInstruction);
  }else{
    return root;
  }
}


tree_t* addTreeIdNode(enum TreeNodeTypes actualNodeToAddType, node_t ** pointerId){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->symbol = pointerId;
  return newNode;
}

tree_t* addTreeIntNode(enum TreeNodeTypes actualNodeToAddType, int value){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->i = value;
  return newNode;
}

tree_t* addTreeFloatNode(enum TreeNodeTypes actualNodeToAddType, float value){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));
  tree_t* newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->f = value;
  return newNode;
}

/*
@param root   syntax tree's current root 
@param instr  instruction to add to the tree

Inserts a new instruction to the tree, usually
when it ends with a semicolon
*/
// solo agrego instrucciones en el mismo nivel
// refactoring
void addInstructionToTree(enum TreeNodeTypes nodeType, func_t * scope){
  printf("Agrego Instruccion, de tipo: %s\n", getTypeOfTree(nodeType));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = nodeType;
  newNode->nextInstruction = NULL;
  newNode->numberOfChilds = -1;
  printf("size: %d\n", scope->heighInstructionStack);

  if(scope->heighInstructionStack > -1){

      if(scope->stack_lastInstruccion[scope->heighInstructionStack] != NULL){
        tree_t * actual =  returnLastInstrucc(scope->stack_lastInstruccion[scope->heighInstructionStack]);
        printf("estoy en %s\n", getTypeOfTree(actual->type));
        actual->nextInstruction = newNode;
        printf("Instruccion agregada\n");
      }

  }else{
      scope->syntaxRoot = newNode;
  }
  printf("sigo vivo\n");
  //connect with last instruction
  //stack_lastInstruccion[heighInstructionStack] = newNode;

}

/*
@param head   symbol's table head
@param name   variable trying to evaluate

Validates if current variables are the same type
*/
void addToExpr(node_t *head, char *name){
  node_t * current = head;
  // find ir in its symbol table
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

void removeFromExpr(node_t *head, char *name){
  name[strlen(name)-1] = '\0';
  printf("Remuevo simbolo con nombre de: %s\n", name);

  node_t * current = head;
  // find ir in its symbol table
  while(current->next != NULL){
    printf("Estoy en: %s\n", current->name);
    current = current->next;
    if (strcmp(current->next->name, name) == 0){
        current->next = NULL;
    }
  }
}



/*
@param head   symbol's table head
@param type   type to add

Adds the type to the last inserted symbol
*/
// refactored
void addTypeToVariable(char *type, func_t* scope){
  if (strcmp(type, "int") == 0){
    scope->lastInserted->type = IntType;
    scope->lastInserted->u_val.i = 0;
  }else{
    scope->lastInserted->type = FloatType;
    scope->lastInserted->u_val.f = 0.0;
  }
}

void addTypeToFunction(char *type){
  printf("agrego tipo a function con name: %s\n", stackFunctions[heighFuncStack]->name);
  if (strcmp(type, "int") == 0){
    stackFunctions[heighFuncStack]->returnType = IntType;
    stackFunctions[heighFuncStack]->i = 0;
  }else{
    stackFunctions[heighFuncStack]->returnType = FloatType;
    stackFunctions[heighFuncStack]->f = 0.0;
  }
}

void pushFunctionInStack(func_t * fun){
  printf("Pusheo function\n");
  heighFuncStack++;
  stackFunctions[heighFuncStack] =  fun;
}

void popFunctionInStack(){
  printf("Popeo function\n");
  stackFunctions[heighFuncStack] =  NULL;
  heighFuncStack--;
}

/*
@param head   symbol's table head
@param name   variable's name

Adds the variable to the symbol table, raises error 
if found previously
*/
void declareVariable(node_t *head, char *name, func_t * scope){
  node_t *current = head;

  printf("agrego variable a function con name: %s\n", stackFunctions[heighFuncStack]->name);

  while(current->next != NULL){
    current = current->next;
    if (strcmp(current->name, name) == 0){
      raiseDuplicateVar(name);
    }
  }
  


  node_t * newNode = (node_t*)malloc(sizeof(node_t));
  current->next = newNode;
  strcpy(newNode->name, name);
  scope->lastInserted = newNode;
}

void declareFunction(func_t * head, char * name){
  func_t *current = head;
  // checo que no haya sido ya declarada
  while(current->next != NULL){
    current = current->next;
    if (strcmp(current->name, name) == 0){
      raiseDuplicateVar(name);
    }
  }
  func_t * newFunc = (func_t*)malloc(sizeof(func_t));
  current->next = newFunc;
  strcpy(newFunc->name, name);
  newFunc->symbolRoot = setTable();
  newFunc->heighInstructionStack = -1;
  newFunc->i = 0;
  newFunc->f = 0.0;
  newFunc->next = NULL;
  newFunc->firstInstruction = true;


  pushFunctionInStack(newFunc);
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
      printf("\t%s - %s : %d\n", head->name, getType(head->type), (head->u_val).i);
    }else{
      printf("\t%s - %s : %f\n", head->name, getType(head->type), (head->u_val).f);
    } 
    printList(head->next);
  }
}

void printFunctionList(func_t* head){
  if(head != NULL){
    printf("-> %s\n", head->name);

    if(head){
        printf("\tSymbol's table:\n");
        printList(head->symbolRoot);
    }

    printFunctionList(head->next);
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

void raiseInvalidParameterType(char *name){
  printf("La variable %s esperaba otro tipo de dato en la función\n", name);
  exit(0);
}
void raiseInvalidAmountOfParameters(){
  printf("El número de parámetros es incorrecto\n");
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
node_t * setTable(){
  node_t * symbol = (node_t*)malloc(sizeof(node_t));
  strcpy(symbol->name, "__init__");
  symbol->next = NULL;
  return symbol;
}

/*
Initializes the syntax tree
*/
void setTree(){
/*   tree_t * syntax = (tree_t*)malloc(sizeof(tree_t));
  syntax->type = INIT;
  syntax->nextInstruction = NULL;
  syntax->numberOfChilds = -1;
  stack_lastInstruccion[heighInstructionStack] = syntax; */
}

/*
@param head   symbol's table head
@param name   variable to be found

Checks if variable exists, raises error if not found
*/
node_t ** verifyID(node_t *head, char *name){
  //printf("Verifico %s\n", name);
  node_t ** current = &head;
  while((*current)->next != NULL){
    current = &((*current)->next);
    if (strcmp((*current)->name, name) == 0){
      return current;
    }
  }
  raiseNoExistingVar(name);
}


func_t ** verifyFunctionID(func_t* head, char* name){
  func_t ** current = &head;
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
  exit(0);
}

void execute(tree_t* actualInstruction){
  printf("Execute type:%s\n", getTypeOfTree(actualInstruction->type));
  printf("Num de hijos: %d\n", actualInstruction->numberOfChilds + 1);

  switch(actualInstruction->type){
    case SetNode:
      printf("ejecuto set, num de hijos: %d\n", actualInstruction->numberOfChilds+1);
      treeEvaluateSet(actualInstruction);
      return;
      break;
    case ReadNode:
      printf("ejecuto read, num de hijos: %d\n", actualInstruction->numberOfChilds+1);
      treeEvaluateRead(actualInstruction);
      return;
      break;
    case PrintNode:
      printf("ejecuto print, num de hijos: %d\n", actualInstruction->numberOfChilds+1);
      treeEvaluatePrint(actualInstruction);
      return;
      break;
    case IfNode:
      printf("ejecuto if, num de hijos: %d\n", actualInstruction->numberOfChilds+1);
      printf("if hijo 0: %s\n", getTypeOfTree(actualInstruction->child[0]->type));
      printf("if hijo 1: %s\n", getTypeOfTree(actualInstruction->child[1]->type));
      treeEvaluateIf(actualInstruction);
      return;
      break;
    case IfelseNode:
      printf("ejecuto ifelse, num de hijos: %d\n", actualInstruction->numberOfChilds+1);
      treeEvaluateIfElse(actualInstruction);
      return;
      break;
    case ForNode:
      printf("ejecuto for, num de hijos: %d\n", actualInstruction->numberOfChilds+1);
      treeEvaluateFor(actualInstruction);
      return;
      break;
    case WhileNode:
      printf("ejecuto while, num de hijos: %d\n", actualInstruction->numberOfChilds+1);
      treeEvaluateWhile(actualInstruction);
      return;
      break;
  }
  // has childrens
  
  if(actualInstruction->numberOfChilds >= 0){
    for(int i = 0; i <= actualInstruction->numberOfChilds; i++){
      execute(actualInstruction->child[i]);
    }
  }
  
  if(actualInstruction->nextInstruction != NULL){
    execute( (actualInstruction->nextInstruction) );
  }
}

void setGlobals(char * name){
  globalFunc = (func_t*)malloc(sizeof(func_t));

  strcpy(globalFunc->name , name);
  globalFunc->symbolRoot = setTable();
  globalFunc->returnType = IntType;
  globalFunc->i = 0;
  globalFunc->heighInstructionStack = -1;
  globalFunc->next = NULL;
  globalFunc->firstInstruction = true;
  // the global func is always the first one
  lastFuncionInserted = globalFunc;
  fsymbol = globalFunc;

  // because when this functiosn its created you will always execute it, add it to the stack
  heighFuncStack++;
  stackFunctions[heighFuncStack] = globalFunc;
}

func_t * createFunc(char * name, enum Types actualreturnType){
  
  func_t * func = (func_t*)malloc(sizeof(func_t));
  strcpy(func->name, name);
  func->symbolRoot = setTable();
  func->returnType = actualreturnType;
  func->heighInstructionStack = -1;
  func->i = 0;
  func->f = 0.0;
  func->next = NULL;
  func->firstInstruction = true;
  return func;
}



int main(int argc, char *argv[]) {
  // Checking if there is an argument
  printf("Bison, syntatic parser:\n");
  if (argc < 2 || argc > 2){ 
    printf("enter 1 argument only eg.\"filename!\"\n"); 
    return 0; 
  } 

  char * file_name = argv[1];  
  FILE * fp  = fopen(file_name, "r"); // read only 

	// check if file exists
	if (fp == NULL) {   
		printf("Error! Could not open file\n"); 
		return 0;
	} 

  yyin = fp; 

  yyparse();  

  if(globalFunc->syntaxRoot){
    printf("Code execution:\n");
    execute(globalFunc->syntaxRoot);
  }

  if(globalFunc){
    printf("Function's table:\n");
    printFunctionList(globalFunc);
  }
    
}