output:  main.c calculator.o string_vector.o stack.o
	gcc main.c calculator.o string_vector.o -o build/main

calculator.o: calculator.c calculator.h
	gcc -c calculator.c

string_vector.o: string_vector.c string_vector.h
	gcc -c string_vector.c

stack.o: stack.c stack.h
	gcc -c stack.c

debug: main.c calculator.c calculator.h string_vector.c string_vector.h stack.c stack.h
	gcc -g main.c calculator.c string_vector.c stack.c -o build/a

clean:
	del *.o

run:
	make
	make debug
	make clean
	./build/main