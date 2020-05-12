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

#ifndef YY_YY_TAREA4_TAB_H_INCLUDED
# define YY_YY_TAREA4_TAB_H_INCLUDED
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
    PROGRAM = 258,
    VAR = 259,
    INT = 260,
    FLOAT = 261,
    SET = 262,
    READ = 263,
    PRINT = 264,
    IF = 265,
    IFELSE = 266,
    WHILE = 267,
    FOR = 268,
    TO = 269,
    STEP = 270,
    DO = 271,
    SUMA = 272,
    RESTA = 273,
    DIVIDE = 274,
    MULTI = 275,
    PAREND = 276,
    PARENI = 277,
    LLAVED = 278,
    LLAVEI = 279,
    COLON = 280,
    SEMICOLON = 281,
    MENOR = 282,
    MAYOR = 283,
    IGUAL = 284,
    MENORI = 285,
    MAYORI = 286,
    NUMI = 287,
    NUMF = 288,
    ID = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 53 "tarea4.y" /* yacc.c:1909  */

  char* stringValue;
  int intValue;
  float floatValue;
  int var_type;
  struct Type* t;

#line 97 "tarea4.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TAREA4_TAB_H_INCLUDED  */
