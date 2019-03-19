CC = g++
BASICFLAGS= 

FLAGS= -Wall $(BASICFLAGS)

OPTFLAG= 

program: grid.o main.o navigator.o
	$(CC) $(FLAGS) grid.o main.o navigator.o -o program

main.o: main.cc main.h
	$(CC) -c main.cc

grid.o: grid.cc grid.h
	$(CC) -c grid.cc

navigator.o: navigator.cc navigator.h
	$(CC) -c navigator.cc

clean:
	rm *.o program

#compile and run
cr:
	make
	./program
