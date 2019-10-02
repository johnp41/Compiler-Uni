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
#line 1 "parser.y" /* yacc.c:339  */

//#include "general.h"
//#include "error.h"
extern "C"{
#include "symbol.h"
}
//#include "symbol.h"
#include  "sem.hpp"
#include "my-ast.hpp"
#include "my-llvm.hpp";
#include <string> 
#include <cstdio>

void yyerror(const char*);
int yylex(void);


extern FILE*    yyin;
Program* t;
bool flag ;
std::list<Local *>  los ;



#line 91 "parser.tab.c" /* yacc.c:339  */

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
    T_array = 258,
    T_begin = 259,
    T_boolean = 260,
    T_char = 261,
    T_dispose = 262,
    T_do = 263,
    T_else = 264,
    T_end = 265,
    T_false = 266,
    T_forward = 267,
    T_function = 268,
    T_goto = 269,
    T_if = 270,
    T_integer = 271,
    T_label = 272,
    T_new = 273,
    T_nil = 274,
    T_not = 275,
    T_of = 276,
    T_or = 277,
    T_procedure = 278,
    T_program = 279,
    T_real = 280,
    T_result = 281,
    T_return = 282,
    T_then = 283,
    T_true = 284,
    T_var = 285,
    T_while = 286,
    T_someth = 287,
    T_gequal = 288,
    T_lequal = 289,
    T_assign = 290,
    T_INTEGER = 291,
    T_ID = 292,
    T_REAL = 293,
    T_CHAR = 294,
    T_STRING = 295,
    T_mod = 296,
    T_div = 297,
    T_and = 298,
    UNMINUS = 299,
    UNPLUS = 300,
    DER = 301,
    RE = 302,
    ARR = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 80 "parser.y" /* yacc.c:355  */


  T_id                            *tid;

  Type   type;
  int    num ;
  float  fl ;
  std::string                     *var;
  char                            op ;
  Program                         *prog ;
  Body                            *bo ;
  std::list<Local *>              *locs  ;  
//  Local     *locs
  std::list<T_id *>                *kat3 , *kat2 ;
  Local                            *kat1 ;
  Header                           *head;
  std::list<Formal *>              *kat4;
  Formal                           *forma;
  Block                            *blck;
  std::list<Stmt *>                *kat8;
  Stmt                             *stm;
  Expr                             *exo;
  char                               yo;
  Lval                             *lval;
  Rval                             *rval;
  Unop                             *unop;
  Binop                            *binop;
  Call                             *call;
  std::list<Expr *>                *kat13;





#line 212 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 229 "parser.tab.c" /* yacc.c:358  */

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
#define YYLAST   452

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  197

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

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
      60,    61,    47,    44,    58,    45,    57,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    56,
      42,    41,    43,     2,    65,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    62,     2,    63,    64,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    46,    49,    50,    51,
      52,    53,    54,    55
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   138,   138,   142,   146,   147,   148,   152,   155,   156,
     162,   163,   164,   176,   177,   189,   196,   197,   206,   207,
     217,   218,   226,   228,   233,   234,   243,   244,   256,   257,
     258,   259,   260,   262,   264,   295,   300,   301,   307,   308,
     314,   315,   316,   317,   320,   322,   323,   324,   325,   326,
     327,   328,   329,   336,   337,   338,   339,   399,   400,   462,
     463,   464,   470,   471,   472,   473,   474,   476,   480,   481,
     485,   489,   493,   497,   500,   504,   507,   510,   513,   516,
     519,   522,   525,   529,   532,   536,   545,   546,   548,   550,
     552,   554,   556,   557,   559,   625,   629,   630,   641,   642
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"array\"", "\"begin\"", "\"boolean\"",
  "\"char\"", "\"dispose\"", "\"do\"", "\"else\"", "\"end\"", "\"false\"",
  "\"forward\"", "\"function\"", "\"goto\"", "\"if\"", "\"integer\"",
  "\"label\"", "\"new\"", "\"nil\"", "\"not\"", "\"of\"", "\"or\"",
  "\"procedure\"", "\"program\"", "\"real\"", "\"result\"", "\"return\"",
  "\"then\"", "\"true\"", "\"var\"", "\"while\"", "\"<>\"", "\">=\"",
  "\"<=\"", "\":=\"", "T_INTEGER", "T_ID", "T_REAL", "T_CHAR", "T_STRING",
  "'='", "'<'", "'>'", "'+'", "'-'", "T_mod", "'*'", "'/'", "T_div",
  "T_and", "UNMINUS", "UNPLUS", "DER", "RE", "ARR", "';'", "'.'", "','",
  "':'", "'('", "')'", "'['", "']'", "'^'", "'@'", "$accept", "program",
  "body", "locals", "vars", "vars2", "local", "kati3", "kati1", "kati2",
  "header", "kati5", "kati4", "formal", "kati6", "type", "block", "kati8",
  "stmt", "notif", "withif", "expr", "lvalue", "lvalue_simple", "rvalue",
  "rvalue_simple", "call", "kati13", "kati14", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,    61,    60,    62,    43,    45,   296,    42,    47,   297,
     298,   299,   300,   301,   302,   303,    59,    46,    44,    58,
      40,    41,    91,    93,    94,    64
};
# endif

#define YYPACT_NINF -67

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-67)))

#define YYTABLE_NINF -94

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-94)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      30,    37,    60,   -26,   -67,   -67,    11,   110,   -67,     2,
      22,    39,    56,    57,    58,   -67,   -67,    40,   -67,   179,
     -67,    63,   147,   185,   -67,   -67,   -67,   -67,   147,   -67,
     -37,   -67,   -67,   -67,   147,    26,   -67,   -67,   -67,   -67,
     -30,    41,    38,    51,    45,    44,   -67,    59,   -67,   -67,
     -67,    61,    42,    54,   -67,   -67,   147,   147,   147,   317,
      54,   -67,    38,   147,    54,   226,     2,   147,   346,     3,
      64,   -67,    26,    41,    -6,   147,   -67,   147,   -67,   -67,
       6,    -5,     6,    29,    58,    68,   217,   -67,   -67,   -67,
     147,     2,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   256,     2,   -67,   -67,   288,
      65,   -67,   -67,     3,   -67,     2,   346,    17,    66,    80,
     -67,    69,    75,   -67,    95,    73,    98,    21,   -67,   -67,
      54,    23,   -67,   127,   375,   375,   375,   375,   375,   375,
      23,    23,   -67,   -67,   -67,   -67,   -67,   217,   -67,   -67,
     147,   -67,   -67,   -67,   -67,   -67,   -67,    31,    78,     6,
     -67,   -67,   -67,   -67,   -18,   -67,   -67,   -67,   -67,    21,
      85,     2,    54,   288,    33,   105,    21,    21,    75,    21,
     108,   -67,   -67,   -67,   -67,   -67,    21,   -67,   -67,   -67,
     -67,   -67,    96,   -67,   139,    21,   -67
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     0,     0,     2,    40,
       0,     0,     0,     0,     0,     6,     5,     0,     3,     0,
      88,     0,     0,     0,    92,    63,    48,    87,     0,    86,
      62,    89,    90,    64,     0,     0,    42,    36,    38,    39,
       0,    59,     0,    43,     0,     0,    16,     0,    13,     8,
       4,    62,     0,    51,    93,    47,     0,     0,     0,     0,
      57,    58,    68,     0,    50,     0,    40,    96,     0,    59,
      58,    62,     0,    94,     0,     0,    60,     0,    61,    12,
      20,     0,    20,     0,     7,     0,     0,    83,    84,    85,
       0,    40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    40,    46,    53,    98,
       0,    67,    91,     0,    35,    40,    41,    59,    58,     0,
      26,     0,    22,    10,     0,     0,     0,     0,     9,    11,
      52,    75,    55,    38,    78,    82,    81,    77,    79,    80,
      69,    70,    74,    71,    72,    73,    76,     0,    45,    54,
       0,    97,    95,    37,    65,    66,    26,     0,     0,     0,
      21,    17,    18,    14,     0,    30,    31,    28,    29,     0,
       0,    40,    49,    98,     0,     0,     0,     0,    22,     0,
       0,    34,    15,    44,    56,    99,     0,    27,    24,    19,
      23,    33,     0,    25,     0,     0,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   111,   -67,   -67,   -67,   -67,   -67,    81,   -67,
     158,    87,    -4,    12,    14,   257,   165,   -67,   -66,   -59,
     -58,    53,    -9,   -16,   -22,    -8,    -7,   -67,     4
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     7,    15,    84,    16,    83,    49,    81,
      17,   121,   160,   122,   157,   170,    36,    74,    37,    38,
      39,    68,    60,    41,    61,    62,    54,   110,   151
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      40,    42,    43,   179,   114,    75,     9,   107,   108,    19,
      53,    42,    70,    20,    64,    42,    21,    22,    69,    73,
      23,    24,    66,    67,   164,   132,   165,   166,    25,    26,
       5,    27,   133,    28,    76,    11,   119,   167,    29,    30,
      31,    32,    33,   120,   180,    13,   168,   148,   149,   153,
     115,   123,    25,   124,     1,   118,   113,    40,    42,    43,
       4,   117,    34,    71,   111,    77,    33,    35,     8,   100,
     101,   102,   103,   104,     3,    59,    45,   130,    42,    77,
     154,    65,    40,    42,    43,   169,    72,   126,   127,   175,
     176,   175,   186,    46,    47,    48,    50,    40,    42,    43,
      55,    79,    78,    77,    80,    86,    40,    42,    43,    87,
      88,    89,   183,   184,     9,   -93,   105,   156,    76,    82,
     109,    67,    10,    11,   129,   112,   152,    12,   116,   155,
     158,   159,   161,    13,   162,   163,   171,   177,   172,    42,
      14,   182,   187,   131,   192,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,    20,   194,
     195,    85,    40,    42,    43,   128,    24,    56,    44,   125,
     174,   178,    18,    25,   190,     0,    27,   185,     0,     0,
       0,     0,     0,    29,    51,    31,    32,    33,     0,     0,
      20,    57,    58,     0,     0,     0,    20,     0,    24,     0,
       0,     0,     0,   173,    24,    25,     0,    34,    27,     0,
       0,    25,    35,     0,    27,    29,    51,    31,    32,    33,
       0,    29,    51,    31,    32,    33,     0,     0,    20,     0,
       0,     0,     0,     0,   106,     0,    24,     0,     0,    34,
       0,    52,     0,    25,    35,    34,    27,    63,    90,     0,
      35,     0,     0,    29,    51,    31,    32,    33,    92,    93,
      94,     0,     0,     0,     0,     0,     0,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,    34,    90,     0,
       0,     0,    35,     0,     0,     0,     0,     0,    92,    93,
      94,     0,     0,     0,     0,     0,     0,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,     0,     0,     0,
      90,     0,     0,     0,     0,     0,     0,     0,     0,   147,
      92,    93,    94,     0,     0,     0,     0,     0,     0,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,    90,
       0,     0,     0,     0,     0,    91,   150,     0,     0,    92,
      93,    94,     0,     0,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,    93,
      94,     0,     0,     0,     0,     0,     0,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -94,   -94,   -94,
       0,     0,     0,     0,     0,     0,   -94,   -94,   -94,    98,
      99,   100,   101,   102,   103,   104,   181,     0,     0,     0,
       0,     0,     0,   188,   189,     0,   191,     0,     0,     0,
       0,     0,     0,   193,     0,     0,     0,     0,     0,     0,
       0,     0,   196
};

static const yytype_int16 yycheck[] =
{
       9,     9,     9,    21,    10,    35,     4,    66,    66,     7,
      19,    19,    34,    11,    23,    23,    14,    15,    34,    35,
      18,    19,    59,    60,     3,    91,     5,     6,    26,    27,
      56,    29,    91,    31,    64,    13,    30,    16,    36,    37,
      38,    39,    40,    37,    62,    23,    25,   106,   106,   115,
      56,    56,    26,    58,    24,    77,    72,    66,    66,    66,
       0,    77,    60,    37,    61,    62,    40,    65,    57,    46,
      47,    48,    49,    50,    37,    22,    37,    86,    86,    62,
      63,    28,    91,    91,    91,    64,    60,    58,    59,    58,
      59,    58,    59,    37,    37,    37,    56,   106,   106,   106,
      37,    56,    64,    62,    60,    63,   115,   115,   115,    56,
      57,    58,   171,   171,     4,    64,    63,    37,    64,    60,
      67,    60,    12,    13,    56,    61,    61,    17,    75,    63,
      61,    56,    37,    23,    61,    37,     9,    59,   147,   147,
      30,    56,    37,    90,    36,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,    11,    63,
      21,    50,   171,   171,   171,    84,    19,    20,    10,    82,
     156,   159,     7,    26,   178,    -1,    29,   173,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    -1,    -1,
      11,    44,    45,    -1,    -1,    -1,    11,    -1,    19,    -1,
      -1,    -1,    -1,   150,    19,    26,    -1,    60,    29,    -1,
      -1,    26,    65,    -1,    29,    36,    37,    38,    39,    40,
      -1,    36,    37,    38,    39,    40,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    19,    -1,    -1,    60,
      -1,    62,    -1,    26,    65,    60,    29,    62,    22,    -1,
      65,    -1,    -1,    36,    37,    38,    39,    40,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    60,    22,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    22,
      -1,    -1,    -1,    -1,    -1,    28,    58,    -1,    -1,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,   169,    -1,    -1,    -1,
      -1,    -1,    -1,   176,   177,    -1,   179,    -1,    -1,    -1,
      -1,    -1,    -1,   186,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   195
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    67,    37,     0,    56,    68,    69,    57,     4,
      12,    13,    17,    23,    30,    70,    72,    76,    82,     7,
      11,    14,    15,    18,    19,    26,    27,    29,    31,    36,
      37,    38,    39,    40,    60,    65,    82,    84,    85,    86,
      88,    89,    91,    92,    76,    37,    37,    37,    37,    74,
      56,    37,    62,    88,    92,    37,    20,    44,    45,    87,
      88,    90,    91,    62,    88,    87,    59,    60,    87,    89,
      90,    37,    60,    89,    83,    35,    64,    62,    64,    56,
      60,    75,    60,    73,    71,    68,    63,    87,    87,    87,
      22,    28,    32,    33,    34,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    87,     8,    85,    86,    87,
      93,    61,    61,    89,    10,    56,    87,    89,    90,    30,
      37,    77,    79,    56,    58,    77,    58,    59,    74,    56,
      88,    87,    84,    85,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    63,    85,    86,
      58,    94,    61,    84,    63,    63,    37,    80,    61,    56,
      78,    37,    61,    37,     3,     5,     6,    16,    25,    64,
      81,     9,    88,    87,    80,    58,    59,    59,    79,    21,
      62,    81,    56,    85,    86,    94,    59,    37,    81,    81,
      78,    81,    36,    81,    63,    21,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    67,    68,    69,    69,    69,    70,    71,    71,
      72,    72,    72,    73,    73,    74,    75,    75,    76,    76,
      77,    77,    78,    78,    79,    79,    80,    80,    81,    81,
      81,    81,    81,    81,    81,    82,    83,    83,    84,    84,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    86,    86,    86,    86,    87,    87,    88,
      88,    88,    89,    89,    89,    89,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    92,    93,    93,    94,    94
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     2,     0,     2,     2,     3,     0,     2,
       4,     4,     3,     0,     3,     5,     0,     3,     5,     7,
       0,     2,     0,     3,     4,     5,     0,     3,     1,     1,
       1,     1,     6,     3,     2,     4,     0,     3,     1,     1,
       0,     3,     1,     1,     6,     4,     3,     2,     1,     5,
       2,     2,     4,     3,     4,     4,     6,     1,     1,     1,
       2,     2,     1,     1,     1,     4,     4,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     1,     1,     1,     1,
       1,     3,     1,     1,     2,     4,     0,     2,     0,     3
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
#line 138 "parser.y" /* yacc.c:1646  */
    {   t = (yyval.prog) = new Program((yyvsp[-3].tid) , (yyvsp[-1].bo)) ; }
#line 1495 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 142 "parser.y" /* yacc.c:1646  */
    { (yyval.bo) = new Body((yyvsp[-1].locs),(yyvsp[0].blck));}
#line 1501 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 146 "parser.y" /* yacc.c:1646  */
    {(yyval.locs) = new std::list<Local *> ;}
#line 1507 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 147 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].locs)->push_back((yyvsp[0].kat1)) ; (yyval.locs)=(yyvsp[-1].locs) ;  }
#line 1513 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].locs)->merge(*(yyvsp[0].locs)) ; (yyval.locs) = (yyvsp[-1].locs) ;}
#line 1519 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 152 "parser.y" /* yacc.c:1646  */
    { (yyvsp[0].locs)->push_back((yyvsp[-1].kat1)) ; (yyval.locs) = (yyvsp[0].locs) ; }
#line 1525 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 155 "parser.y" /* yacc.c:1646  */
    {(yyval.locs) = new std::list<Local *> ;}
#line 1531 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 156 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-1].locs)->push_back((yyvsp[0].kat1)) ; (yyval.locs) = (yyvsp[-1].locs) ;}
#line 1537 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 162 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-1].kat3)->push_back((yyvsp[-2].tid)); (yyval.kat1) = new Local(label,(yyvsp[-1].kat3)); flag = false ;}
#line 1543 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 163 "parser.y" /* yacc.c:1646  */
    {(yyval.kat1) = new Local(header,(yyvsp[-3].head),(yyvsp[-1].bo)); flag = false ;}
#line 1549 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 164 "parser.y" /* yacc.c:1646  */
    {(yyval.kat1) = new Local(forwad,(yyvsp[-1].head)); flag = false ;}
#line 1555 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 176 "parser.y" /* yacc.c:1646  */
    {(yyval.kat3) = new std::list<T_id *> ;}
#line 1561 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 177 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-2].kat3)->push_back((yyvsp[0].tid));
                                  
                                  (yyval.kat3) = (yyvsp[-2].kat3) ;}
#line 1569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 189 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-3].kat3)->push_back((yyvsp[-4].tid))  ;     (yyval.kat1) = new Local(var,(yyvsp[-3].kat3),(yyvsp[-1].type));  }
#line 1575 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 196 "parser.y" /* yacc.c:1646  */
    {(yyval.kat3) = new std::list<T_id *>;}
#line 1581 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 197 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-2].kat3)->push_back((yyvsp[0].tid)); (yyval.kat3) = (yyvsp[-2].kat3) ;}
#line 1587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 206 "parser.y" /* yacc.c:1646  */
    {(yyval.head) = new Header(procedure,(yyvsp[-3].tid),(yyvsp[-1].kat4));}
#line 1593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 207 "parser.y" /* yacc.c:1646  */
    {(yyval.head) = new Header(function,(yyvsp[-5].tid),(yyvsp[-3].kat4),(yyvsp[0].type));}
#line 1599 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 217 "parser.y" /* yacc.c:1646  */
    {(yyval.kat4) = {} ;}
#line 1605 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 218 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].kat4)->push_back((yyvsp[-1].forma));(yyval.kat4) = (yyvsp[0].kat4) ;}
#line 1611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 226 "parser.y" /* yacc.c:1646  */
    {(yyval.kat4) = new std::list<Formal *> ;}
#line 1617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 228 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].kat4)->push_back((yyvsp[-1].forma));(yyval.kat4) =  (yyvsp[0].kat4) ;}
#line 1623 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 233 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-2].kat3)->push_back((yyvsp[-3].tid)); (yyval.forma) = new Formal(value,(yyvsp[-2].kat3),(yyvsp[0].type));}
#line 1629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 234 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-2].kat3)->push_back((yyvsp[-3].tid)); (yyval.forma) = new Formal(refernce,(yyvsp[-2].kat3),(yyvsp[0].type));}
#line 1635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 243 "parser.y" /* yacc.c:1646  */
    {(yyval.kat3) = new std::list<T_id *>;}
#line 1641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 244 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-2].kat3)->push_back((yyvsp[0].tid));(yyval.kat3) = (yyvsp[-2].kat3) ;}
#line 1647 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 256 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = typeInteger;}
#line 1653 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 257 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = typeReal; }
#line 1659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 258 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = typeBoolean; }
#line 1665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 259 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = typeChar;}
#line 1671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 260 "parser.y" /* yacc.c:1646  */
    {(yyval.type) =typeArray((yyvsp[-3].num),(yyvsp[0].type));}
#line 1677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 262 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = typeIArray((yyvsp[0].type)) ;}
#line 1683 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 264 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = typePointer((yyvsp[0].type));}
#line 1689 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 295 "parser.y" /* yacc.c:1646  */
    {(yyval.blck) = new Block((yyvsp[-2].stm),(yyvsp[-1].kat8));}
#line 1695 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 300 "parser.y" /* yacc.c:1646  */
    {(yyval.kat8) = new std::list<Stmt *>;}
#line 1701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 301 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-2].kat8)->push_back((yyvsp[0].stm));(yyval.kat8) = (yyvsp[-2].kat8) ;}
#line 1707 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 307 "parser.y" /* yacc.c:1646  */
    { (yyval.stm) = (yyvsp[0].stm) ;}
#line 1713 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 308 "parser.y" /* yacc.c:1646  */
    { (yyval.stm) = (yyvsp[0].stm) ; }
#line 1719 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 314 "parser.y" /* yacc.c:1646  */
    { (yyval.stm) =  NULL ;}
#line 1725 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 315 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tlva,(yyvsp[-2].lval),(yyvsp[0].exo));}
#line 1731 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 316 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tblock,(yyvsp[0].blck));}
#line 1737 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 317 "parser.y" /* yacc.c:1646  */
    {  (yyval.stm) = new Stmt(tcall,(yyvsp[0].call));}
#line 1743 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 320 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tif,(yyvsp[-4].exo),(yyvsp[-2].stm),(yyvsp[0].stm));}
#line 1749 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 322 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(twhile,(yyvsp[-2].exo),(yyvsp[0].stm));}
#line 1755 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 323 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tid,(yyvsp[-2].tid),(yyvsp[0].stm));}
#line 1761 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 324 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tgoto,(yyvsp[0].tid));}
#line 1767 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 325 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(treturn);}
#line 1773 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 326 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tnew_ex,(yyvsp[0].lval),(yyvsp[-2].exo));}
#line 1779 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 327 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tnew,(yyvsp[0].lval),NULL);}
#line 1785 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 328 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tdispose,(yyvsp[0].lval));}
#line 1791 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 329 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tdispose_ar,(yyvsp[0].lval));}
#line 1797 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 336 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tid,(yyvsp[-2].tid),(yyvsp[0].stm));}
#line 1803 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 337 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(twhile,(yyvsp[-2].exo),(yyvsp[0].stm));}
#line 1809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 338 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tif,(yyvsp[-2].exo),(yyvsp[0].stm)); }
#line 1815 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 339 "parser.y" /* yacc.c:1646  */
    {(yyval.stm) = new Stmt(tif,(yyvsp[-4].exo),(yyvsp[-2].stm),(yyvsp[0].stm));}
#line 1821 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 399 "parser.y" /* yacc.c:1646  */
    {(yyval.exo) = new Expr(lva,(yyvsp[0].lval),NULL);}
#line 1827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 400 "parser.y" /* yacc.c:1646  */
    {(yyval.exo) = new Expr(rva,NULL,(yyvsp[0].rval));}
#line 1833 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 462 "parser.y" /* yacc.c:1646  */
    {(yyval.lval) = (yyvsp[0].lval);}
#line 1839 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 463 "parser.y" /* yacc.c:1646  */
    {(yyval.lval) = new Lval(tref_lv , NULL,"",(yyvsp[-1].lval),NULL,NULL);   }
#line 1845 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 464 "parser.y" /* yacc.c:1646  */
    {(yyval.lval) = new Lval(tref_rv,NULL,"",NULL,NULL,(yyvsp[-1].rval)); }
#line 1851 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 470 "parser.y" /* yacc.c:1646  */
    {(yyval.lval) = new Lval(tid_l,(yyvsp[0].tid),"",NULL,NULL,NULL);}
#line 1857 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 471 "parser.y" /* yacc.c:1646  */
    {(yyval.lval) = new Lval(tresult_l,NULL,"",NULL,NULL,NULL);}
#line 1863 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 472 "parser.y" /* yacc.c:1646  */
    {(yyval.lval) = new Lval(tstring_l,NULL,*((yyvsp[0].var)),NULL,NULL,NULL);}
#line 1869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 473 "parser.y" /* yacc.c:1646  */
    {(yyval.lval) = new Lval(tarr_l,NULL,"",(yyvsp[-3].lval),(yyvsp[-1].lval),NULL);}
#line 1875 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 474 "parser.y" /* yacc.c:1646  */
    {(yyval.lval) = new Lval(tarr_r,NULL,"",(yyvsp[-3].lval),NULL,(yyvsp[-1].rval));}
#line 1881 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 476 "parser.y" /* yacc.c:1646  */
    {(yyval.lval) = new Lval(t_group_l,NULL,"",(yyvsp[-1].lval),NULL,NULL);}
#line 1887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 480 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = (yyvsp[0].rval) ;}
#line 1893 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 482 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tplus_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1899 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 486 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tminus_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1905 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 490 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tmul_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1911 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 494 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tslash_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1917 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 498 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tdiv_r , 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1923 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 501 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tmod_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1929 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 505 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tor_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1935 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 508 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tand_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1941 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 511 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tequal_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1947 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 514 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(twhot_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1953 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 517 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tless_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1959 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 520 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tge_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1965 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 523 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tleseq_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1971 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 526 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tgeq_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[-2].exo),(yyvsp[0].exo));}
#line 1977 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 530 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tnot_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[0].exo),NULL);}
#line 1983 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 533 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tuplus_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[0].exo),NULL);}
#line 1989 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 537 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tuminus_r, 0,'0',0.0,NULL,NULL,NULL,NULL,(yyvsp[0].exo),NULL);}
#line 1995 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 545 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tint_r,(yyvsp[0].num),'0',0.0,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 2001 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 546 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tbool_r, 0,'t',0.0,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 2007 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 548 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tbool_r, 0,'f',0.0,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 2013 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 550 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(treal_r, 0,'0',(yyvsp[0].fl),NULL,NULL,NULL,NULL,NULL,NULL);}
#line 2019 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 552 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tchar_r, 0,'0',0.0,(yyvsp[0].op),NULL,NULL,NULL,NULL);}
#line 2025 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 554 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(trval_r, 0,'0',0.0,NULL,(yyvsp[-1].rval),NULL,NULL,NULL,NULL);}
#line 2031 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 556 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tnill_r,0,'0',0.0,NULL,NULL,NULL,NULL,NULL,NULL);}
#line 2037 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 557 "parser.y" /* yacc.c:1646  */
    { (yyval.rval) = new Rval(tcall_r, 0,'0',0.0,NULL,NULL,NULL,(yyvsp[0].call),NULL,NULL);}
#line 2043 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 560 "parser.y" /* yacc.c:1646  */
    {(yyval.rval) = new Rval(tderfe_r, 0,'0',0.0,NULL,NULL,(yyvsp[0].lval),NULL,NULL,NULL);}
#line 2049 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 625 "parser.y" /* yacc.c:1646  */
    {(yyval.call) = new Call((yyvsp[-3].tid),(yyvsp[-1].kat13));}
#line 2055 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 629 "parser.y" /* yacc.c:1646  */
    {(yyval.kat13) = new std::list<Expr *>;}
#line 2061 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 630 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].kat13)->push_back((yyvsp[-1].exo)); (yyval.kat13) = (yyvsp[0].kat13) ;}
#line 2067 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 641 "parser.y" /* yacc.c:1646  */
    {(yyval.kat13) = new std::list<Expr *>;}
#line 2073 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 642 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].kat13)->push_back((yyvsp[-1].exo)); (yyval.kat13) = (yyvsp[0].kat13) ;}
#line 2079 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2083 "parser.tab.c" /* yacc.c:1646  */
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
#line 648 "parser.y" /* yacc.c:1906  */






int main(int argc,char* argv[]) {
  if(argc==2){
        yyin = fopen(argv[1], "r");
  }
 // cout << "eimai edw" << endl ;
  int result = yyparse();
  if (result != 0) exit(1);
  initSymbolTable(997);
 // cout << "ksekinaw semantic" << endl;
  
  sem_prog(t);
  //cout << "teleiwsa semanti" << endl;
  compile(t);
  destroySymbolTable();
  return 0 ;
}
