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
    NUMI = 258,
    NUMF = 259,
    PROGRAM = 260,
    VAR = 261,
    INT = 262,
    FLOAT = 263,
    SET = 264,
    READ = 265,
    PRINT = 266,
    IF = 267,
    IFELSE = 268,
    WHILE = 269,
    FOR = 270,
    TO = 271,
    STEP = 272,
    DO = 273,
    ID = 274,
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
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TAREA4_TAB_H_INCLUDED  */
