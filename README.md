# Tarea 5

Compile instructions:

`flex tarea5.flex && bison -d tarea5.y && gcc lex.yy.c tarea5.tab.c -lfl -lm`

or:

`flex tarea5.flex`

`bison -d tarea5.y`

`gcc lex.yy.c tarea5.tab.c -lfl -lm`

And for testing purposes, 8 files are provided:

`./a.out tests/prueba5.txt`

Output:

Symbol table in format:
Variable Type
row by row until all table is printed

Except if error is found, will prompt wich error is and terminate the program
