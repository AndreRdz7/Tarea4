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
// not used rn
void addInstructionToParent(tree_t*, enum TreeNodeTypes);
// add instruction node
void addInstructionToTree();
// create a node that has wo childs (expr, term, expresion)
void pushStackLastInstruccion();
void popStackLastInstruccion();
tree_t* createBinaryNode(enum TreeNodeTypes, tree_t*, tree_t*);
tree_t* addTreeNode(enum TreeNodeTypes);
tree_t* addTreeIdNode(enum TreeNodeTypes, node_t **);
tree_t* addTreeIntNode(enum TreeNodeTypes, int);
tree_t* addTreeFloatNode(enum TreeNodeTypes, float);
char* getTypeOfTree(enum TreeNodeTypes);
void GenerateNodeAccordingToType(enum TreeNodeTypes);




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
tree_t* lastTreeNode; //last node in the tree that was added

int heighStack = -1;
tree_t * stack_lastInstruccion[100]; // last instruction of the tree


#line 176 "tarea5.tab.c" /* yacc.c:339  */

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
    MAYORI = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 111 "tarea5.y" /* yacc.c:355  */

  char* stringValue;
  char* terminal;
  char* type;
  float f;
  int i;
  struct Tree *tree_t;

#line 260 "tarea5.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TAREA5_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 277 "tarea5.tab.c" /* yacc.c:358  */

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
#define YYLAST   86

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  110

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   133,   133,   136,   137,   140,   141,   144,   144,   147,
     148,   151,   151,   152,   153,   154,   157,   157,   157,   157,
     158,   158,   158,   159,   159,   162,   162,   162,   163,   163,
     166,   166,   167,   167,   167,   167,   167,   170,   171,   171,
     171,   174,   175,   178,   179,   180,   183,   184,   185,   187,
     188,   189,   190,   193,   194,   195,   196,   197
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
  "IGUAL", "MENORI", "MAYORI", "$accept", "prog", "opt_decls", "decls",
  "dec", "$@1", "tipo", "stmt", "$@2", "assig_stmt", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "if_stmt", "$@9", "$@10", "$@11", "iter_stmt",
  "$@12", "$@13", "$@14", "$@15", "$@16", "cmp_stmt", "$@17", "$@18",
  "stmt_lst", "expr", "term", "factor", "expresion", YY_NULLPTR
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
     285,   286,   287,   288,   289
};
# endif

#define YYPACT_NINF -34

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-34)))

#define YYTABLE_NINF -40

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       5,    14,    21,    30,   -34,    46,    53,    33,   -34,    31,
     -34,    23,    46,    35,   -34,    39,    40,    56,    42,   -34,
      13,   -34,   -34,   -34,   -34,    37,    44,    -3,    -3,    65,
     -34,    23,   -34,   -34,    -3,   -34,   -34,   -34,   -34,    -3,
     -34,   -34,   -34,    -3,   -17,    20,   -34,   -34,   -34,   -34,
     -34,    18,    66,    68,    26,   -34,   -12,    -3,    -3,    -3,
      -3,    -3,    -3,    -3,    -3,    -3,    50,    51,    -3,   -34,
      52,   -34,   -34,    47,    55,   -34,    20,    20,    26,    26,
      26,    26,    26,   -34,   -34,    23,    23,    26,   -34,    -3,
      54,   -34,    23,    23,   -34,    63,    26,   -34,   -34,   -34,
      -3,    57,    26,   -34,    64,    -3,    26,    62,    23,   -34
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     0,     0,     3,     6,
       7,    11,     0,     0,    25,     0,     0,     0,    38,     2,
       0,    13,    14,    15,     5,     0,     0,     0,     0,     0,
      37,    11,    16,    20,     0,    12,     9,    10,     8,     0,
      50,    51,    52,     0,     0,    45,    48,    28,    30,    32,
      41,    11,     0,     0,    23,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
       0,    17,    21,     0,     0,    49,    43,    44,    53,    54,
      55,    56,    57,    47,    46,    11,    11,    33,    40,     0,
       0,    24,    11,    11,    31,     0,    18,    22,    27,    29,
       0,     0,    34,    19,     0,     0,    35,     0,    11,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -34,   -34,   -34,    72,   -34,   -34,   -34,   -31,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -33,    -9,   -13,   -21
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,     8,     9,    13,    38,    19,    20,    35,
      52,    89,   101,    53,    90,    73,    21,    26,    74,    66,
      22,    67,    68,    95,   104,   107,    23,    31,    70,    51,
      44,    45,    46,    47
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      50,    54,    40,    57,    58,    41,    42,    48,    57,    58,
      56,     1,    75,    59,    60,    61,    62,    63,    55,     3,
      69,     4,    43,    32,    33,    34,    78,    79,    80,    81,
      82,    14,    15,    16,    17,    87,    14,    15,    16,    17,
      36,    37,    64,    65,   -39,    18,    57,    58,    76,    77,
      18,    83,    84,     6,    93,    94,    96,     5,    10,    11,
      12,    98,    99,    25,    27,    28,    29,   102,    30,    39,
      49,    71,   106,    72,    85,    86,    91,   109,    88,    92,
     100,   108,   105,    97,    24,     0,   103
};

static const yytype_int8 yycheck[] =
{
      31,    34,     5,    20,    21,     8,     9,    28,    20,    21,
      43,     6,    24,    30,    31,    32,    33,    34,    39,     5,
      51,     0,    25,    10,    11,    12,    59,    60,    61,    62,
      63,    13,    14,    15,    16,    68,    13,    14,    15,    16,
       3,     4,    22,    23,    26,    27,    20,    21,    57,    58,
      27,    64,    65,     7,    85,    86,    89,    27,     5,    26,
      29,    92,    93,    28,    25,    25,    10,   100,    26,    25,
       5,     5,   105,     5,    24,    24,    29,   108,    26,    24,
      17,    19,    18,    29,    12,    -1,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    36,     5,     0,    27,     7,    37,    38,    39,
       5,    26,    29,    40,    13,    14,    15,    16,    27,    42,
      43,    51,    55,    61,    38,    28,    52,    25,    25,    10,
      26,    62,    10,    11,    12,    44,     3,     4,    41,    25,
       5,     8,     9,    25,    65,    66,    67,    68,    68,     5,
      42,    64,    45,    48,    65,    68,    65,    20,    21,    30,
      31,    32,    33,    34,    22,    23,    54,    56,    57,    42,
      63,     5,     5,    50,    53,    24,    66,    66,    65,    65,
      65,    65,    65,    67,    67,    24,    24,    65,    26,    46,
      49,    29,    24,    42,    42,    58,    65,    29,    42,    42,
      17,    47,    65,    29,    59,    18,    65,    60,    19,    42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    40,    39,    41,
      41,    43,    42,    42,    42,    42,    45,    46,    47,    44,
      48,    49,    44,    50,    44,    52,    53,    51,    54,    51,
      56,    55,    57,    58,    59,    60,    55,    61,    62,    63,
      61,    64,    64,    65,    65,    65,    66,    66,    66,    67,
      67,    67,    67,    68,    68,    68,    68,    68
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     1,     0,     3,     1,     0,     5,     1,
       1,     0,     2,     1,     1,     1,     0,     0,     0,     7,
       0,     0,     5,     0,     4,     0,     0,     7,     0,     7,
       0,     6,     0,     0,     0,     0,    14,     2,     0,     0,
       5,     1,     2,     3,     3,     1,     3,     3,     1,     3,
       1,     1,     1,     3,     3,     3,     3,     3
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
#line 144 "tarea5.y" /* yacc.c:1646  */
    {declareVariable(symbol, yylval.stringValue);}
#line 1422 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 147 "tarea5.y" /* yacc.c:1646  */
    {addTypeToVariable(symbol, yylval.type);}
#line 1428 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 148 "tarea5.y" /* yacc.c:1646  */
    {addTypeToVariable(symbol, yylval.type);}
#line 1434 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 151 "tarea5.y" /* yacc.c:1646  */
    {addInstructionToTree();}
#line 1440 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 157 "tarea5.y" /* yacc.c:1646  */
    {addTreeNode(SetNode);}
#line 1446 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 157 "tarea5.y" /* yacc.c:1646  */
    {addTreeIdNode(IdNode, verifyID(symbol, yylval.stringValue));}
#line 1452 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 157 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1458 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 158 "tarea5.y" /* yacc.c:1646  */
    {addTreeNode(ReadNode);}
#line 1464 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 158 "tarea5.y" /* yacc.c:1646  */
    {addTreeIdNode(IdNode, verifyID(symbol, yylval.stringValue));}
#line 1470 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 159 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1476 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 162 "tarea5.y" /* yacc.c:1646  */
    {addTreeNode(IfNode);}
#line 1482 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 162 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1488 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 163 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1494 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 166 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1500 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 167 "tarea5.y" /* yacc.c:1646  */
    {addTreeIdNode(IdNode, verifyID(symbol, yylval.stringValue));}
#line 1506 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 167 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1512 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 167 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1518 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 167 "tarea5.y" /* yacc.c:1646  */
    {resetHeap();}
#line 1524 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 171 "tarea5.y" /* yacc.c:1646  */
    {pushStackLastInstruccion();}
#line 1530 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 171 "tarea5.y" /* yacc.c:1646  */
    {popStackLastInstruccion();}
#line 1536 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 178 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(SumaNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1542 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 179 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(RestaNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1548 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 180 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1554 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 183 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MultNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1560 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 184 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(DivideNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1566 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 185 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[0].tree_t);}
#line 1572 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 187 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = (yyvsp[-1].tree_t);}
#line 1578 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 188 "tarea5.y" /* yacc.c:1646  */
    {addToExpr(symbol, yylval.stringValue); (yyval.tree_t) = addTreeIdNode(IdNode, verifyID(symbol, yylval.stringValue));}
#line 1584 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 189 "tarea5.y" /* yacc.c:1646  */
    {intToHeap(); (yyval.tree_t) = addTreeIntNode(IntNode, yylval.i);}
#line 1590 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 190 "tarea5.y" /* yacc.c:1646  */
    {floatToHeap(); (yyval.tree_t) = addTreeFloatNode(FloatNode, yylval.f);}
#line 1596 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 193 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MenorNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1602 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 194 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MayorNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1608 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 195 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(IgualNode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1614 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 196 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MenorINode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1620 "tarea5.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 197 "tarea5.y" /* yacc.c:1646  */
    {(yyval.tree_t) = createBinaryNode(MayorINode, (yyvsp[-2].tree_t), (yyvsp[0].tree_t));}
#line 1626 "tarea5.tab.c" /* yacc.c:1646  */
    break;


#line 1630 "tarea5.tab.c" /* yacc.c:1646  */
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
#line 200 "tarea5.y" /* yacc.c:1906  */


char* getTypeOfTree(enum TreeNodeTypes type) 
{
      switch (type) 
      {
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

void pushStackLastInstruccion(){
  printf("Creo nueva lista de instrucciones\n");
  heighStack++;
}

void popStackLastInstruccion(){
  printf("Termino lista de instrucciones y regreso a la pasada\n");
  stack_lastInstruccion[heighStack] = NULL;
  heighStack--;
}

tree_t* addTreeNode(enum TreeNodeTypes actualNodeToAddType){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));

  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  lastTreeNode->numberOfChilds++;
  lastTreeNode->child[lastTreeNode->numberOfChilds] = newNode;
  //esto solo ocurre aqui, no en binary node o en nodos leaft:
  lastTreeNode = newNode;
  return newNode;
}

tree_t* addTreeIdNode(enum TreeNodeTypes actualNodeToAddType, node_t ** pointerId){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));

  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->symbol = pointerId;
  lastTreeNode->numberOfChilds++;
  lastTreeNode->child[lastTreeNode->numberOfChilds] = newNode;
  return newNode;
}

tree_t* addTreeIntNode(enum TreeNodeTypes actualNodeToAddType, int value){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));

  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->i = value;
  lastTreeNode->numberOfChilds++;
  lastTreeNode->child[lastTreeNode->numberOfChilds] = newNode;

  return newNode;
}

tree_t* addTreeFloatNode(enum TreeNodeTypes actualNodeToAddType, float value){
  printf("Agrego nodo, de tipo: %s\n", getTypeOfTree(actualNodeToAddType));

  tree_t* newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  newNode->type = actualNodeToAddType;
  newNode->f = value;
  lastTreeNode->numberOfChilds++;
  lastTreeNode->child[lastTreeNode->numberOfChilds] = newNode;

  return newNode;
}

/*
@param root   syntax tree's current root 
@param instr  instruction to add to the tree

Inserts a new instruction to the tree, usually
when it ends with a semicolon
*/
// solo agrego instrucciones en el mismo nivel
void addInstructionToTree(){
  printf("Agrego Instruccion\n");
  tree_t * newNode = (tree_t*)malloc(sizeof(tree_t));
  newNode->numberOfChilds = -1;
  enum TreeNodeTypes actualInstruccion = InstruccionNode;
  newNode->type = actualInstruccion;
  newNode->nextInstruction = NULL;
  stack_lastInstruccion[heighStack] = newNode;
  lastTreeNode = newNode;
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
}

/*
@param head   symbol's table head
@param name   variable to be found

Checks if variable exists, raises error if not found
*/
node_t ** verifyID(node_t *head, char *name){
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
}