/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "tarea5.y" /* yacc.c:339  */


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
enum TreeNodeTypes{INIT, FuncionNode , MayorNode ,MenorNode, IgualNode, MenorINode, MayorINode, InstruccionNode, IdNode, ExprNode, ReturnNode, ReadNode, PrintNode, IfNode, ExpresionNode, IfelseNode, WhileNode, ForNode, SetNode, ComparandumNode, RestaNode, SumaNode, MultNode, DivideNode, TermNode, IntNode, FloatNode};

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

int counterP = 0;

enum Types heap = NULLType;


tree_t  * actualFuncNode;
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


node_t ** verifyFID(node_t*, char*);
//check if value exists and if the type is the same (taht we are keeping in the heap)
void addToExpr(node_t*, char*);
// int or float type selection

void addTypeToVariable(char*, func_t*);

void counterParams(func_t*);


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
bool evaluatePameters(tree_t* node);


tree_t * createFunctionNode(func_t*);

tree_t * connectWithFunction(tree_t *);


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
void raiseWrongReturnType(char* name);


// symbol, last Inserted , syntax, stack function height and the stack of main function
// by every func created a new symbol, lastInserted, syntax, heigh and stack will be declared
// and stored in the node of function
func_t * globalFunc;


func_t * fsymbol; // start of the linked list of functions
func_t * lastFuncionInserted; // last function declared

char * idName;
node_t ** pointerToMemoryOfID;


#line 253 "tarea5.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "tarea5.tab.h".  */
#ifndef YY_YY_TAREA5_TAB_H_INCLUDED
# define YY_YY_TAREA5_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    ID = 260,
    FUN = 261,
    PROGRAM = 262,
    VAR = 263,
    NUMI = 264,
    NUMF = 265,
    SET = 266,
    READ = 267,
    PRINT = 268,
    IF = 269,
    IFELSE = 270,
    WHILE = 271,
    FOR = 272,
    TO = 273,
    STEP = 274,
    DO = 275,
    SUMA = 276,
    RESTA = 277,
    DIVIDE = 278,
    MULTI = 279,
    PAREND = 280,
    PARENI = 281,
    LLAVED = 282,
    LLAVEI = 283,
    COLON = 284,
    SEMICOLON = 285,
    MENOR = 286,
    MAYOR = 287,
    IGUAL = 288,
    MENORI = 289,
    MAYORI = 290,
    COMMA = 291,
    RETURN = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 188 "tarea5.y" /* yacc.c:355  */

  char* stringValue;
  char* terminal;
  char* type;
  float f;
  int i;
  struct Tree *tree_t;

#line 340 "tarea5.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TAREA5_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 357 "tarea5.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   117

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   209,   209,   209,   212,   213,   216,   217,   220,   220,
     223,   224,   227,   228,   231,   232,   235,   235,   235,   235,
     235,   238,   239,   242,   243,   246,   246,   247,   250,   250,
     253,   253,   254,   255,   256,   260,   260,   260,   261,   261,
     262,   262,   263,   263,   266,   266,   267,   267,   270,   270,
     271,   271,   271,   271,   271,   274,   275,   275,   275,   278,
     279,   282,   283,   284,   287,   288,   289,   291,   292,   292,
     293,   294,   297,   297,   298,   302,   303,   306,   307,   310,
     311,   312,   313,   314
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "FUN", "PROGRAM",
  "VAR", "NUMI", "NUMF", "SET", "READ", "PRINT", "IF", "IFELSE", "WHILE",
  "FOR", "TO", "STEP", "DO", "SUMA", "RESTA", "DIVIDE", "MULTI", "PAREND",
  "PARENI", "LLAVED", "LLAVEI", "COLON", "SEMICOLON", "MENOR", "MAYOR",
  "IGUAL", "MENORI", "MAYORI", "COMMA", "RETURN", "$accept", "prog", "$@1",
  "opt_decls", "decls", "dec", "$@2", "tipo", "opt_fun_decls", "fun_decls",
  "fun_dec", "$@3", "$@4", "$@5", "$@6", "fun_op", "oparams", "params",
  "$@7", "param", "$@8", "stmt", "$@9", "assig_stmt", "$@10", "$@11",
  "$@12", "$@13", "$@14", "if_stmt", "$@15", "$@16", "iter_stmt", "$@17",
  "$@18", "$@19", "$@20", "$@21", "cmp_stmt", "$@22", "$@23", "stmt_lst",
  "expr", "term", "factor", "$@24", "factor_id", "$@25", "opt_exprs",
  "expr_lst", "expresion", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

#define YYPACT_NINF -74

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-74)))

#define YYTABLE_NINF -58

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      11,    34,    44,   -74,   -74,    32,    53,    57,    61,   -74,
      33,   -74,    63,    42,    61,   -74,    53,    41,   -74,     0,
     -74,   -74,    17,    45,    46,    47,    49,    65,    50,   -74,
      -8,   -74,   -74,   -74,   -74,   -74,   -74,   -74,     1,     1,
       1,    74,   -74,     0,    75,    76,     1,     1,   -74,    77,
     -74,   -74,   -74,     1,    -9,    23,   -74,   -74,   -74,   -74,
     -74,   -74,    21,   -74,   -74,    29,    29,    78,   -74,   -74,
      59,    56,    20,     1,     1,     1,     1,     1,     1,     1,
       1,     1,    64,    66,    68,     1,   -74,    67,     1,    58,
      60,    69,   -74,    70,    62,   -74,   -74,   -74,    23,    23,
      29,    29,    29,    29,    29,   -74,   -74,     0,     0,     0,
      29,   -74,    29,   -74,   -74,   -74,    72,    73,    77,     1,
     -74,     0,   -74,    79,    80,    17,    17,   -74,    29,    71,
      81,   -74,     1,   -74,   -74,   -74,   -74,     1,    29,   -21,
      29,    84,    53,   -74,   -74,     1,    82,    29,     0,    86,
     -74,     0,   -74
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     5,     0,    13,     4,
       7,     8,     0,     0,    12,    15,     0,     0,    16,    30,
      14,     6,     0,     0,     0,     0,     0,     0,    56,     3,
       0,    32,    33,    34,    10,    11,     9,    17,     0,     0,
       0,     0,    55,    30,     0,     0,     0,     0,    31,    24,
      68,    70,    71,     0,     0,    63,    66,    44,    46,    48,
      50,    59,    30,    35,    38,    40,    42,     0,    18,    23,
      25,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,     0,     0,
       0,     0,    28,     0,     0,    72,    69,    67,    61,    62,
      79,    80,    81,    82,    83,    65,    64,    30,    30,    30,
      51,    58,    36,    39,    41,    43,     0,     0,     0,    76,
      45,    30,    49,     0,     0,     0,     0,    26,    78,     0,
      75,    47,     0,    37,    29,    19,    73,     0,    52,     0,
      77,     0,     5,    22,    20,     0,     0,    53,    30,     0,
      21,    30,    54
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,   -74,   -56,    88,   -74,   -74,   -73,   -74,   -74,
      93,   -74,   -74,   -74,   -74,   -74,   -74,    -7,   -74,   -74,
     -74,   -43,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   -45,   -19,   -24,   -74,   -74,   -74,   -74,   -74,
      19
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,     8,     9,    10,    17,    36,    13,    14,
      15,    23,    49,    93,   139,   144,    68,    69,    94,    70,
     116,    29,    30,    48,    88,   124,    89,    90,    91,    31,
      82,    83,    32,    84,    85,   123,   141,   149,    33,    43,
      87,    62,    54,    55,    56,    71,    96,   119,   129,   130,
      57
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    65,    66,    44,    45,    46,    50,   142,    72,   143,
      51,    52,    73,    74,    24,    25,    26,    27,     1,    86,
      34,    35,    75,    76,    77,    78,    79,    53,    28,    47,
     100,   101,   102,   103,   104,    24,    25,    26,    27,     3,
     110,    73,    74,   112,     4,    97,    80,    81,   -57,    28,
      73,    74,   134,   135,    98,    99,   105,   106,    58,    59,
       6,     7,    11,    16,   120,   121,   122,    12,    18,    19,
      22,    37,    38,    39,   128,    40,    41,    42,   131,    60,
      63,    64,    95,    92,   -27,    67,   146,   138,   113,   107,
     114,   108,   140,   109,   111,   117,   136,   132,   118,   115,
     147,   125,   126,   145,    21,   150,   151,    20,   152,   148,
     133,   127,     0,     0,     0,     0,     0,   137
};

static const yytype_int16 yycheck[] =
{
      43,    46,    47,    11,    12,    13,     5,    28,    53,    30,
       9,    10,    21,    22,    14,    15,    16,    17,     7,    62,
       3,     4,    31,    32,    33,    34,    35,    26,    28,    37,
      75,    76,    77,    78,    79,    14,    15,    16,    17,     5,
      85,    21,    22,    88,     0,    25,    23,    24,    27,    28,
      21,    22,   125,   126,    73,    74,    80,    81,    39,    40,
      28,     8,     5,    30,   107,   108,   109,     6,     5,    27,
      29,    26,    26,    26,   119,    26,    11,    27,   121,     5,
       5,     5,    26,     5,    25,     8,   142,   132,    30,    25,
      30,    25,   137,    25,    27,    25,    25,    18,    36,    30,
     145,    29,    29,    19,    16,   148,    20,    14,   151,    27,
      30,   118,    -1,    -1,    -1,    -1,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    39,     5,     0,    40,    28,     8,    41,    42,
      43,     5,     6,    46,    47,    48,    30,    44,     5,    27,
      48,    42,    29,    49,    14,    15,    16,    17,    28,    59,
      60,    67,    70,    76,     3,     4,    45,    26,    26,    26,
      26,    11,    27,    77,    11,    12,    13,    37,    61,    50,
       5,     9,    10,    26,    80,    81,    82,    88,    88,    88,
       5,    59,    79,     5,     5,    80,    80,     8,    54,    55,
      57,    83,    80,    21,    22,    31,    32,    33,    34,    35,
      23,    24,    68,    69,    71,    72,    59,    78,    62,    64,
      65,    66,     5,    51,    56,    26,    84,    25,    81,    81,
      80,    80,    80,    80,    80,    82,    82,    25,    25,    25,
      80,    27,    80,    30,    30,    30,    58,    25,    36,    85,
      59,    59,    59,    73,    63,    29,    29,    55,    80,    86,
      87,    59,    18,    30,    45,    45,    25,    36,    80,    52,
      80,    74,    28,    30,    53,    19,    41,    80,    27,    75,
      59,    20,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    40,    39,    41,    41,    42,    42,    44,    43,
      45,    45,    46,    46,    47,    47,    49,    50,    51,    52,
      48,    53,    53,    54,    54,    56,    55,    55,    58,    57,
      60,    59,    59,    59,    59,    62,    63,    61,    64,    61,
      65,    61,    66,    61,    68,    67,    69,    67,    71,    70,
      72,    73,    74,    75,    70,    76,    77,    78,    76,    79,
      79,    80,    80,    80,    81,    81,    81,    82,    83,    82,
      82,    82,    85,    84,    84,    86,    86,    87,    87,    88,
      88,    88,    88,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     8,     1,     0,     3,     1,     0,     5,
       1,     1,     1,     0,     2,     1,     0,     0,     0,     0,
      12,     4,     1,     1,     0,     0,     4,     1,     0,     5,
       0,     2,     1,     1,     1,     0,     0,     6,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     7,     0,     6,
       0,     0,     0,     0,    14,     2,     0,     0,     5,     1,
       2,     3,     3,     1,     3,     3,     1,     3,     0,     3,
       1,     1,     0,     4,     0,     1,     0,     3,     1,     3,
       3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 209 "tarea5.y" /* yacc.c:1646  */
    {setGlobals(yylval.stringValue);}
#line 1540 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 220 "tarea5.y" /* yacc.c:1646  */
    {declareVariable(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue, stackFunctions[heighFuncStack]);}
#line 1546 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 220 "tarea5.y" /* yacc.c:1646  */
    {addTypeToVariable(yylval.type, stackFunctions[heighFuncStack]);}
#line 1552 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 235 "tarea5.y" /* yacc.c:1646  */
    {declareFunction(fsymbol, yylval.stringValue);}
#line 1558 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 235 "tarea5.y" /* yacc.c:1646  */
    {counterP = 0;}
#line 1564 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 235 "tarea5.y" /* yacc.c:1646  */
    {counterParams(stackFunctions[heighFuncStack]);}
#line 1570 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 235 "tarea5.y" /* yacc.c:1646  */
    {addTypeToFunction(yylval.type);}
#line 1576 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 235 "tarea5.y" /* yacc.c:1646  */
    {popFunctionInStack();}
#line 1582 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 238 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1588 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 246 "tarea5.y" /* yacc.c:1646  */
    {counterP++;}
#line 1594 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 247 "tarea5.y" /* yacc.c:1646  */
    {counterP++;}
#line 1600 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 250 "tarea5.y" /* yacc.c:1646  */
    {declareVariable(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue, stackFunctions[heighFuncStack]);}
#line 1606 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 250 "tarea5.y" /* yacc.c:1646  */
    {addTypeToVariable(yylval.type, stackFunctions[heighFuncStack]);}
#line 1612 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 253 "tarea5.y" /* yacc.c:1646  */
    {addInstructionToTree(InstruccionNode, stackFunctions[heighFuncStack]);}
#line 1618 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 253 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1624 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 254 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1630 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 255 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1636 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 256 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1642 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 260 "tarea5.y" /* yacc.c:1646  */
    {pointerToMemoryOfID = verifyID(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue);}
#line 1648 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 260 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1654 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 260 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createBinaryNode(SetNode, addTreeIdNode(IdNode, pointerToMemoryOfID), (yyvsp[-2].tree_t)), stackFunctions[heighFuncStack]);}
#line 1660 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 261 "tarea5.y" /* yacc.c:1646  */
    {pointerToMemoryOfID = verifyID(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue);}
#line 1666 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 261 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createUnaryNode(ReadNode, addTreeIdNode(IdNode, pointerToMemoryOfID)), stackFunctions[heighFuncStack]);}
#line 1672 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 262 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1678 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 262 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createUnaryNode(PrintNode, (yyvsp[-2].tree_t)), stackFunctions[heighFuncStack]);}
#line 1684 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 263 "tarea5.y" /* yacc.c:1646  */
    {resetHeap(); printf("Termino de leer expr de return\n");}
#line 1690 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 263 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createUnaryNode(ReturnNode, (yyvsp[-2].tree_t)), stackFunctions[heighFuncStack]);}
#line 1696 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 266 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1702 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 266 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createBinaryNode(IfNode,(yyvsp[-3].tree_t), (yyvsp[0].tree_t)), stackFunctions[heighFuncStack]);}
#line 1708 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 267 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1714 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 267 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createTernaryNode(IfelseNode, (yyvsp[-4].tree_t), (yyvsp[-1].tree_t), (yyvsp[0].tree_t)), stackFunctions[heighFuncStack]);}
#line 1720 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 270 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1726 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 270 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createBinaryNode(WhileNode, (yyvsp[-3].tree_t), (yyvsp[0].tree_t)), stackFunctions[heighFuncStack]);}
#line 1732 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 271 "tarea5.y" /* yacc.c:1646  */
    {pointerToMemoryOfID = verifyID(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue);}
#line 1738 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 271 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1744 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 271 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1750 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 271 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1756 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 271 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createQuaternaryNode(ForNode, createBinaryNode(SetNode, addTreeIdNode(IdNode, pointerToMemoryOfID), (yyvsp[-9].tree_t)), (yyvsp[-6].tree_t), (yyvsp[-3].tree_t), (yyvsp[0].tree_t)), stackFunctions[heighFuncStack]);}
#line 1762 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 274 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = NULL;}
#line 1768 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 275 "tarea5.y" /* yacc.c:1646  */
    {pushStackLastInstruccion(stackFunctions[heighFuncStack]);}
#line 1774 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 275 "tarea5.y" /* yacc.c:1646  */
    {popStackLastInstruccion(stackFunctions[heighFuncStack]);}
#line 1780 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 275 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[-2].tree_t);}
#line 1786 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 278 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1792 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 279 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1798 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 282 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(SumaNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1804 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 283 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(RestaNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1810 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 284 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1816 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 287 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MultNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1822 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 288 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(DivideNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1828 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 289 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1834 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 291 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[-1].tree_t);}
#line 1840 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 292 "tarea5.y" /* yacc.c:1646  */
    {idName = (yyvsp[0].stringValue); addToExpr(stackFunctions[heighFuncStack]->symbolRoot, yylval.stringValue);}
#line 1846 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 292 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1852 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 293 "tarea5.y" /* yacc.c:1646  */
    {intToHeap(); (yyval.tree_t) = addTreeIntNode(IntNode, yylval.i);}
#line 1858 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 294 "tarea5.y" /* yacc.c:1646  */
    {floatToHeap(); (yyval.tree_t) = addTreeFloatNode(FloatNode, yylval.f);}
#line 1864 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 297 "tarea5.y" /* yacc.c:1646  */
    {actualFuncNode = createFunctionNode(stackFunctions[heighFuncStack]);}
#line 1870 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 297 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = actualFuncNode;}
#line 1876 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 298 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = addTreeIdNode(IdNode, verifyFID(stackFunctions[heighFuncStack]->symbolRoot, idName ));}
#line 1882 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 306 "tarea5.y" /* yacc.c:1646  */
    {connectWithFunction((yyvsp[0].tree_t));}
#line 1888 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 307 "tarea5.y" /* yacc.c:1646  */
    {connectWithFunction((yyvsp[0].tree_t));}
#line 1894 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 310 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MenorNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1900 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 311 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MayorNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1906 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 312 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(IgualNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1912 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 313 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MenorINode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1918 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 314 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MayorINode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1924 "tarea5.tab.c" /* yacc.c:1646  */
    break;


#line 1928 "tarea5.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 317 "tarea5.y" /* yacc.c:1906  */


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
  //printf("Actual heigh of stack: %d\n", actualScope->heighInstructionStack);

  if(actualScope->heighInstructionStack > -1){
    tree_t * lastNodeInList = returnLastInstrucc(actualScope->stack_lastInstruccion[actualScope->heighInstructionStack]);
    //printf("Es: %s\n",getTypeOfTree(lastNodeInList->type));
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
  printf("printing... ");
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

void counterParams(func_t* fun){
  fun->numParams = counterP;
  counterP = 0;
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
  int numParams = node->funcNode->numParams;
  if(numParams != node->numberOfChilds){
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
  //printf("Left: %s\n", getTypeOfTree(left->type));
  //printf("hijos de left: %d\n", left->numberOfChilds+1);
  //printf("Right: %s\n", getTypeOfTree(right->type));
  //printf("hijos de right: %d\n", right->numberOfChilds+1);

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
  printf("Agrego ID nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->symbol = pointerId;
  return newNode;
}


tree_t * createFunctionNode(func_t * func){
  printf("Agrego Funcion nodo, de tipo: %s\n", getTypeOfTree(FuncionNode));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = FuncionNode;
  newNode->funcNode = func;
  return newNode;
}

tree_t * connectWithFunction(tree_t * child){
  printf("Le agrego un param al nodo funcion llamado: %s\n", actualFuncNode->funcNode->name);
  printf("Agrego el param de tipo: %s\n", getTypeOfTree(child->type));
  actualFuncNode->numberOfChilds++;
  actualFuncNode->child[actualFuncNode->numberOfChilds] = child;
  return actualFuncNode;
}

tree_t* addTreeIntNode(enum TreeNodeTypes actualNodeToAddType, int value){
  printf("Agrego INT nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->i = value;
  return newNode;
}

tree_t* addTreeFloatNode(enum TreeNodeTypes actualNodeToAddType, float value){
  printf("Agrego FLOAT nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));
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
  //printf("size: %d\n", scope->heighInstructionStack);

  if(scope->heighInstructionStack > -1){

      if(scope->stack_lastInstruccion[scope->heighInstructionStack] != NULL){
        tree_t * actual =  returnLastInstrucc(scope->stack_lastInstruccion[scope->heighInstructionStack]);
        //printf("estoy en %s\n", getTypeOfTree(actual->type));
        actual->nextInstruction = newNode;
        //printf("Instruccion agregada\n");
      }

  }else{
      scope->syntaxRoot = newNode;
  }
  
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
  newFunc->numParams = 0;
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
    printf("Num de params: %d\n", head->numParams);

    if(head){
        printf("\tSymbol's table:\n");
        if(head->symbolRoot->next){
          printList(head->symbolRoot->next);
        }else{
          printf("No variables declared\n");
        }
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
void raiseWrongReturnType(char *name){
  printf("El valor de retorno para la funcion %s es inválido\n", name);
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


node_t ** verifyFID(node_t *head, char *name){
  name[strlen(name)-1] = '\0';
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
      //printf("Hijo derecha: %s\n", getTypeOfTree(actualInstruction->child[1]->type));
      //printf("Hijo de func: %s\n", getTypeOfTree(actualInstruction->child[1]->child[0]->type));
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
  globalFunc->numParams = 0;
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
  func->numParams = 0;
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
  printf("-------------------------------------------------------------------------------\n");
  if(globalFunc->syntaxRoot){
    printf("Code execution:\n");
    execute(globalFunc->syntaxRoot);
  }

  if(globalFunc){
    printf("Function's table:\n");
    printFunctionList(globalFunc);
  }
    
}
