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

typedef struct Func{
  char name[256];
  enum Types returnType;
  int i;
  float f;
  struct Func * next;
  struct Tree * treeRoot;
  struct Node * exprRoot;
} func_t;



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


int firstInstruction = true;

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


// functions of creating functions
void setFuncionsTable();
void declareFunction(func_t*, char*);
func_t ** verifyFunctionID(func_t*, char*);
void printFunctionList(func_t*);

//ERRORS
void raiseDuplicateVar(char* name);
void raiseInvalidType(char* name);
void raiseInvalidCompatibleTypes();
void raiseNoExistingVar(char* name);



node_t* symbol; // start of the symbol linked list
node_t* lastInserted; // last element inserted in the linked list

func_t * fsymbol; // start of the linked list of functions
func_t * lastFuncionInserted; // last function declared

tree_t* syntax; //start of the syntax tree


int heighStack = -1;
tree_t * stack_lastInstruccion[100]; // last instruction of the tree
node_t ** pointerToMemoryOfID;


#line 219 "tarea5.tab.c" /* yacc.c:339  */

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
    PROGRAM = 261,
    VAR = 262,
    NUMI = 263,
    NUMF = 264,
    SET = 265,
    READ = 266,
    PRINT = 267,
    IF = 268,
    IFELSE = 269,
    WHILE = 270,
    FOR = 271,
    TO = 272,
    STEP = 273,
    DO = 274,
    SUMA = 275,
    RESTA = 276,
    DIVIDE = 277,
    MULTI = 278,
    PAREND = 279,
    PARENI = 280,
    LLAVED = 281,
    LLAVEI = 282,
    COLON = 283,
    SEMICOLON = 284,
    MENOR = 285,
    MAYOR = 286,
    IGUAL = 287,
    MENORI = 288,
    MAYORI = 289,
    COMMA = 290,
    RETURN = 291,
    FUN = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 154 "tarea5.y" /* yacc.c:355  */

  char* stringValue;
  char* terminal;
  char* type;
  float f;
  int i;
  struct Tree *tree_t;

#line 306 "tarea5.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TAREA5_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 323 "tarea5.tab.c" /* yacc.c:358  */

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
#define YYLAST   122

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

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
       0,   175,   175,   178,   179,   182,   183,   186,   186,   189,
     190,   193,   194,   197,   198,   201,   201,   202,   202,   205,
     206,   209,   210,   213,   216,   216,   217,   218,   219,   223,
     223,   223,   224,   224,   225,   225,   226,   229,   229,   230,
     230,   233,   233,   234,   234,   234,   234,   234,   237,   238,
     238,   238,   241,   242,   245,   246,   247,   250,   251,   252,
     254,   255,   256,   257,   258,   258,   261,   262,   265,   266,
     269,   270,   271,   272,   273
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "PROGRAM", "VAR",
  "NUMI", "NUMF", "SET", "READ", "PRINT", "IF", "IFELSE", "WHILE", "FOR",
  "TO", "STEP", "DO", "SUMA", "RESTA", "DIVIDE", "MULTI", "PAREND",
  "PARENI", "LLAVED", "LLAVEI", "COLON", "SEMICOLON", "MENOR", "MAYOR",
  "IGUAL", "MENORI", "MAYORI", "COMMA", "RETURN", "FUN", "$accept", "prog",
  "opt_decls", "decls", "dec", "$@1", "tipo", "opt_fun_decls", "fun_decls",
  "fun_dec", "$@2", "$@3", "oparams", "params", "param", "stmt", "$@4",
  "assig_stmt", "$@5", "$@6", "$@7", "$@8", "if_stmt", "$@9", "$@10",
  "iter_stmt", "$@11", "$@12", "$@13", "$@14", "$@15", "cmp_stmt", "$@16",
  "$@17", "stmt_lst", "expr", "term", "factor", "$@18", "opt_exprs",
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

#define YYPACT_NINF -67

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-67)))

#define YYTABLE_NINF -51

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       5,    17,    32,    16,   -67,    41,    46,    28,   -67,    34,
     -67,    59,    40,    28,   -67,    41,    43,   -67,     0,   -67,
     -67,    42,    45,    47,    48,    49,    50,    66,    51,   -67,
      -7,   -67,   -67,   -67,   -67,   -67,   -67,    71,    71,     1,
       1,     1,    74,   -67,     0,    75,    76,     1,     1,   -67,
      78,    60,   -67,    53,    61,   -67,   -67,   -67,     1,   -13,
      27,   -67,   -67,   -67,   -67,   -67,   -67,    26,   -67,   -67,
      35,    35,    58,    62,    71,    63,    68,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,    69,    70,    77,
       1,   -67,    72,     1,    79,    80,    42,    42,   -67,    42,
       1,   -67,    27,    27,    35,    35,    35,    35,    35,   -67,
     -67,     0,     0,     0,    35,   -67,    35,   -67,   -67,   -67,
      73,    81,    35,    82,    64,   -67,     0,   -67,    86,    83,
      41,   -67,   -67,     1,   -67,     1,   -67,    85,    35,    35,
       0,    87,   -67,     1,    35,    94,     0,   -67
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     0,    12,     3,     6,
       7,     0,     0,    11,    14,     0,     0,    15,    24,    13,
       5,     0,     0,     0,     0,     0,     0,     0,    49,     2,
       0,    26,    27,    28,     9,    10,     8,    20,    20,     0,
       0,     0,     0,    48,    24,     0,     0,     0,     0,    25,
       0,     0,    19,    22,     0,    61,    62,    63,     0,     0,
      56,    59,    37,    39,    41,    43,    52,    24,    29,    32,
      34,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    53,     0,     0,     0,     0,     0,     0,    21,     0,
       0,    60,    54,    55,    70,    71,    72,    73,    74,    58,
      57,    24,    24,    24,    44,    51,    30,    33,    35,    23,
       0,     0,    69,     0,    66,    38,    24,    42,     0,     0,
       4,    18,    65,     0,    40,     0,    31,     0,    68,    45,
      24,     0,    16,     0,    46,     0,    24,    47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -67,   -67,   -35,    89,   -67,   -67,   -66,   -67,   -67,    93,
     -67,   -67,    84,    44,   -67,   -44,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -46,   -21,   -26,   -67,   -67,
     -67,    21
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,     8,     9,    16,    36,    12,    13,    14,
      22,    23,    51,    52,    53,    29,    30,    49,    93,   129,
      94,    95,    31,    87,    88,    32,    89,    90,   128,   141,
     145,    33,    44,    92,    67,    59,    60,    61,    76,   123,
     124,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    70,    71,    45,    46,    47,    55,    78,    79,    56,
      57,     1,    77,    24,    25,    26,    27,    80,    81,    82,
      83,    84,     3,    91,    78,    79,    58,    28,   101,    48,
     119,   120,     4,   121,   104,   105,   106,   107,   108,    24,
      25,    26,    27,     5,   114,    34,    35,   116,     6,    85,
      86,    10,   -50,    28,   122,    78,    79,   102,   103,   109,
     110,    63,    64,    15,    17,    11,    18,   125,   126,   127,
      37,    21,    38,    39,    40,    41,    42,    43,    50,    65,
      68,    69,   134,    72,    73,    75,    96,   138,    74,   139,
      97,    99,   100,   111,   112,   137,   142,   144,   115,   133,
     130,   113,   147,   135,    20,   143,    19,   132,   117,   118,
     131,   140,   136,   146,     0,     0,     0,     0,    98,     0,
       0,     0,    54
};

static const yytype_int16 yycheck[] =
{
      44,    47,    48,    10,    11,    12,     5,    20,    21,     8,
       9,     6,    58,    13,    14,    15,    16,    30,    31,    32,
      33,    34,     5,    67,    20,    21,    25,    27,    24,    36,
      96,    97,     0,    99,    80,    81,    82,    83,    84,    13,
      14,    15,    16,    27,    90,     3,     4,    93,     7,    22,
      23,     5,    26,    27,   100,    20,    21,    78,    79,    85,
      86,    40,    41,    29,     5,    37,    26,   111,   112,   113,
      25,    28,    25,    25,    25,    25,    10,    26,     7,     5,
       5,     5,   126,     5,    24,    24,    28,   133,    35,   135,
      28,    28,    24,    24,    24,   130,   140,   143,    26,    35,
      27,    24,   146,    17,    15,    18,    13,    25,    29,    29,
      29,    26,    29,    19,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    39,     5,     0,    27,     7,    40,    41,    42,
       5,    37,    45,    46,    47,    29,    43,     5,    26,    47,
      41,    28,    48,    49,    13,    14,    15,    16,    27,    53,
      54,    60,    63,    69,     3,     4,    44,    25,    25,    25,
      25,    25,    10,    26,    70,    10,    11,    12,    36,    55,
       7,    50,    51,    52,    50,     5,     8,     9,    25,    73,
      74,    75,    79,    79,    79,     5,    53,    72,     5,     5,
      73,    73,     5,    24,    35,    24,    76,    73,    20,    21,
      30,    31,    32,    33,    34,    22,    23,    61,    62,    64,
      65,    53,    71,    56,    58,    59,    28,    28,    51,    28,
      24,    24,    74,    74,    73,    73,    73,    73,    73,    75,
      75,    24,    24,    24,    73,    26,    73,    29,    29,    44,
      44,    44,    73,    77,    78,    53,    53,    53,    66,    57,
      27,    29,    25,    35,    53,    17,    29,    40,    73,    73,
      26,    67,    53,    18,    73,    68,    19,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    43,    42,    44,
      44,    45,    45,    46,    46,    48,    47,    49,    47,    50,
      50,    51,    51,    52,    54,    53,    53,    53,    53,    56,
      57,    55,    58,    55,    59,    55,    55,    61,    60,    62,
      60,    64,    63,    65,    66,    67,    68,    63,    69,    70,
      71,    69,    72,    72,    73,    73,    73,    74,    74,    74,
      75,    75,    75,    75,    76,    75,    77,    77,    78,    78,
      79,    79,    79,    79,    79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     7,     1,     0,     3,     1,     0,     5,     1,
       1,     1,     0,     2,     1,     0,    12,     0,     9,     1,
       0,     3,     1,     4,     0,     2,     1,     1,     1,     0,
       0,     6,     0,     4,     0,     4,     2,     0,     6,     0,
       7,     0,     6,     0,     0,     0,     0,    14,     2,     0,
       0,     5,     1,     2,     3,     3,     1,     3,     3,     1,
       3,     1,     1,     1,     0,     5,     1,     0,     3,     1,
       3,     3,     3,     3,     3
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
        case 7:
#line 186 "tarea5.y" /* yacc.c:1646  */
    {declareVariable(symbol, yylval.stringValue);}
#line 1499 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 189 "tarea5.y" /* yacc.c:1646  */
    {addTypeToVariable(symbol, yylval.type);}
#line 1505 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 190 "tarea5.y" /* yacc.c:1646  */
    {addTypeToVariable(symbol, yylval.type);}
#line 1511 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 201 "tarea5.y" /* yacc.c:1646  */
    {declareFunction(fsymbol, yylval.stringValue)}
#line 1517 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 202 "tarea5.y" /* yacc.c:1646  */
    {declareFunction(fsymbol, yylval.stringValue)}
#line 1523 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 216 "tarea5.y" /* yacc.c:1646  */
    {addInstructionToTree(InstruccionNode);}
#line 1529 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 216 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1535 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 217 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1541 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 218 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1547 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 219 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1553 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 223 "tarea5.y" /* yacc.c:1646  */
    {pointerToMemoryOfID = verifyID(symbol, yylval.stringValue);}
#line 1559 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 223 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1565 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 223 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createBinaryNode(SetNode, addTreeIdNode(IdNode, pointerToMemoryOfID), (yyvsp[-2].tree_t)));}
#line 1571 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 224 "tarea5.y" /* yacc.c:1646  */
    {pointerToMemoryOfID = verifyID(symbol, yylval.stringValue);}
#line 1577 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 224 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createUnaryNode(ReadNode, addTreeIdNode(IdNode, pointerToMemoryOfID)));}
#line 1583 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 225 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1589 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 225 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createUnaryNode(PrintNode, (yyvsp[-2].tree_t)));}
#line 1595 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 229 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1601 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 229 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createBinaryNode(IfNode,(yyvsp[-3].tree_t), (yyvsp[0].tree_t)));}
#line 1607 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 230 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1613 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 230 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createTernaryNode(IfelseNode, (yyvsp[-4].tree_t), (yyvsp[-1].tree_t), (yyvsp[0].tree_t)));}
#line 1619 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 233 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1625 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 233 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createBinaryNode(WhileNode, (yyvsp[-3].tree_t), (yyvsp[0].tree_t)));}
#line 1631 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 234 "tarea5.y" /* yacc.c:1646  */
    {pointerToMemoryOfID = verifyID(symbol, yylval.stringValue);}
#line 1637 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 234 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1643 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 234 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1649 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 234 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1655 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 234 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = connectWithInstruccion(createQuaternaryNode(ForNode, createBinaryNode(SetNode, addTreeIdNode(IdNode, pointerToMemoryOfID), (yyvsp[-9].tree_t)), (yyvsp[-6].tree_t), (yyvsp[-3].tree_t), (yyvsp[0].tree_t)));}
#line 1661 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 237 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = NULL;}
#line 1667 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 238 "tarea5.y" /* yacc.c:1646  */
    {pushStackLastInstruccion();}
#line 1673 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 238 "tarea5.y" /* yacc.c:1646  */
    {popStackLastInstruccion();}
#line 1679 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 238 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[-2].tree_t);}
#line 1685 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 241 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1691 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 242 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1697 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 245 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(SumaNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1703 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 246 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(RestaNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1709 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 247 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1715 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 250 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MultNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1721 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 251 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(DivideNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1727 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 252 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1733 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 254 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[-1].tree_t);}
#line 1739 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 255 "tarea5.y" /* yacc.c:1646  */
    {addToExpr(symbol, yylval.stringValue); (yyval.tree_t) = addTreeIdNode(IdNode, verifyID(symbol, yylval.stringValue));}
#line 1745 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 256 "tarea5.y" /* yacc.c:1646  */
    {intToHeap(); (yyval.tree_t) = addTreeIntNode(IntNode, yylval.i);}
#line 1751 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 257 "tarea5.y" /* yacc.c:1646  */
    {floatToHeap(); (yyval.tree_t) = addTreeFloatNode(FloatNode, yylval.f);}
#line 1757 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 258 "tarea5.y" /* yacc.c:1646  */
    {addToExpr(symbol, yylval.stringValue); verifyFunctionID(fsymbol, yylval.stringValue);}
#line 1763 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 269 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MenorNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1769 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 270 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MayorNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1775 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 271 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(IgualNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1781 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 272 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MenorINode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1787 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 273 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MayorINode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1793 "tarea5.tab.c" /* yacc.c:1646  */
    break;


#line 1797 "tarea5.tab.c" /* yacc.c:1646  */
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
#line 276 "tarea5.y" /* yacc.c:1906  */


char* getTypeOfTree(enum TreeNodeTypes type) {
  switch (type) {
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

tree_t* connectWithInstruccion(tree_t * subtree){
  // printf("Connecto, subgrafo a la instruccion actual, el tipo del subgrafo es: %s\n",getTypeOfTree(subtree->type));
  // printf("Actual heigh of tsack: %d\n", heighStack);
  tree_t * lastNodeInList = returnLastInstrucc(stack_lastInstruccion[heighStack]);
  // printf("Es: %s\n",getTypeOfTree(lastNodeInList->type));
  lastNodeInList->numberOfChilds = lastNodeInList->numberOfChilds + 1;
  lastNodeInList->child[lastNodeInList->numberOfChilds] = subtree;
  return (stack_lastInstruccion[heighStack]);
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

tree_t* createQuaternaryNode(enum TreeNodeTypes type, tree_t * one, tree_t * two, tree_t * three, tree_t* four){
  // printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(type));
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

tree_t* createTernaryNode(enum TreeNodeTypes type, tree_t * one, tree_t * two, tree_t * three){
  // printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(type));
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
  // printf("Creando Binary\n");
  // printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(type));
  // printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
  // printf("Left: %s\n", getTypeOfTree(left->type));
  // printf("hijos de left: %d\n", left->numberOfChilds+1);
  // printf("Right: %s\n", getTypeOfTree(right->type));
  // printf("hijos de right: %d\n", right->numberOfChilds+1);

  if(right->nextInstruction != NULL){
    // printf("Next instruction: %s\n", getTypeOfTree(right->nextInstruction->type));
  }else{
    // printf("No ahy next instr\n");
  }
  if(right->numberOfChilds > -1){
    // printf("Mmm: %s\n", getTypeOfTree(right->child[0]->type));
  }
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

tree_t* createUnaryNode(enum TreeNodeTypes type, tree_t *child){
  // printf("Creando Unary\n");
  // printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(type));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = type;
  newNode->nextInstruction = NULL;
  newNode->numberOfChilds = -1;
  newNode->numberOfChilds++;
  newNode->child[newNode->numberOfChilds] = child;
  return newNode;
}

void pushStackLastInstruccion(){
  // printf("Creo nueva lista de instrucciones\n");
  heighStack++;
  tree_t * init_node = (tree_t*)malloc(sizeof(tree_t));
  init_node->type = INIT;
  init_node->nextInstruction = NULL;
  init_node->numberOfChilds = -1;
  stack_lastInstruccion[heighStack] = init_node;

  
  if(firstInstruction){
    syntax = init_node;
    firstInstruction = false;
  }
}

void popStackLastInstruccion(){
  // printf("Termino lista de instrucciones y regreso a la pasada\n");
  stack_lastInstruccion[heighStack] = NULL;
  heighStack--;
}

tree_t * returnLastInstrucc(tree_t * root){
  if(root->nextInstruction){
    returnLastInstrucc(root->nextInstruction);
  }else{
    return root;
  }
}


tree_t* addTreeIdNode(enum TreeNodeTypes actualNodeToAddType, node_t ** pointerId){
  // printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->symbol = pointerId;
  return newNode;
}

tree_t* addTreeIntNode(enum TreeNodeTypes actualNodeToAddType, int value){
  // printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->i = value;
  return newNode;
}

tree_t* addTreeFloatNode(enum TreeNodeTypes actualNodeToAddType, float value){
  // printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));
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
void addInstructionToTree(enum TreeNodeTypes nodeType){
  // printf("Agrego Instruccion\n");
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->type = nodeType;
  newNode->nextInstruction = NULL;
  newNode->numberOfChilds = -1;
  if(stack_lastInstruccion[heighStack] != NULL){
    returnLastInstrucc(stack_lastInstruccion[heighStack])->nextInstruction = newNode;
    // printf("Instruccion agregada\n");
  }
  //connect with last instruction
  //stack_lastInstruccion[heighStack] = newNode;

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

void declareFunction(func_t * head, char * name){
  func_t *current = head;
  while(current->next != NULL){
    current = current->next;
    if (strcmp(current->name, name) == 0){
      raiseDuplicateVar(name);
    }
  }
  func_t * newNode = (func_t*)malloc(sizeof(func_t));
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

void printFunctionList(func_t* head){
  if(head != NULL){
    printf("%s\n", head->name);
  }
  printFunctionList(head->next);
  
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

void setFuncionsTable(){
  fsymbol = (func_t*)malloc(sizeof(func_t));
  strcpy(fsymbol->name, "__init__");
  fsymbol->next = NULL;
  lastFuncionInserted = fsymbol;
}
/*
Initializes the syntax tree
*/
void setTree(){
  syntax = (tree_t*)malloc(sizeof(tree_t));
  syntax->type = INIT;
  syntax->nextInstruction = NULL;
  syntax->numberOfChilds = -1;
  stack_lastInstruccion[heighStack] = syntax;
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

  setTable();
  setFuncionsTable();
  //setTree();
  yyparse();  
  printf("Code execution:\n");
  execute(syntax);
  printf("Symbol's table:\n");
  printList(symbol->next);
}
