all: program1 program2 program3 timer.o

program1: program1.c
	gcc -o program1 program1.c -g

program2: program2.c
	gcc -o program2 program2.c -g

program3: program3.c
	gcc -o program3 program3.c -g

timer.o: timer.c
	gcc -c timer.c -g

clean:
	rm -f *.o
	rm -f program1
	rm -f program2
	rm -f program3
	rm -f *~
