Just compile with gcc main.c -o someOut
Or gcc -g -fsanitize=leak -o myprogram main.c for memory leak checking 
Run ./someOut
Gl