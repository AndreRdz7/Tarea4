# Tarea 4

Compile instructions:

`flex tarea4.lex`

`bison -d tarea4.y`

`gcc lex.yy.c tarea4.tab.c -lfl -lm`

And for testing purposes, 8 files are provided:

`./a.out prueba1.txt`

Output:

Symbol table in format:
Variable Type
row by row until all table is printed

Except if error is found, will prompt wich error is and terminate the program
