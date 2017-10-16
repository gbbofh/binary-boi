all: main

main: main.c ops.o cpu.o
	gcc -o main main.c ops.o cpu.o -g


ops.o: ops.c
	gcc -o ops.o -c ops.c -g

cpu.o: cpu.c
	gcc -o cpu.o -c cpu.c -g


.PHONY:

clean:
	-rm *.o
