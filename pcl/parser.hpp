/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
#line 80 "parser.y" /* yacc.c:1909  */


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





#line 138 "parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
