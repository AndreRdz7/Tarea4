# Tarea 4

Compile instructions:

`flex tarea4.lex`

`bison -d tarea4.y`

`gcc lex.yy.c tarea4.tab.c -lfl -lm`

And for testing purposes, 8 files are provided:

`./a.out prueba1.txt`
